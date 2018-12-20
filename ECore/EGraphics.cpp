#include "EGraphics.h"
#include "EUtil.h"

namespace E3D
{
    EBitmap::EBitmap(const EString &filename) :name(filename), pixels(NULL),
        pitch(0), width(0), height(0), valid(false)
    {
        //materials
        hBitmap = (HBITMAP)::LoadImage(GHInstance, GetPath(filename).c_str(), IMAGE_BITMAP,
            0, 0, LR_LOADFROMFILE);

        if (hBitmap != NULL)   
        {
            bitmapHDC = ::CreateCompatibleDC(NULL);
            ::SelectObject(bitmapHDC, (HGDIOBJ)hBitmap);
            ::GetObject(hBitmap, sizeof(BITMAP), &bitmap);

            width   = bitmap.bmWidth;
            height  = bitmap.bmHeight;
            pitch   = bitmap.bmHeight;
            valid   = true;

            pixels = new EColor[width * height];
            for (EInt i = 0; i < getHeight(); ++i)
            {
                for (EInt j = 0; j < getWidth(); ++j) {
                    COLORREF color = ::GetPixel(bitmapHDC, i, j);
                    pixels[j*width + i] = EColor(GetRValue(color), GetGValue(color),
                        GetBValue(color));
                }
            }
        }
    }

    //destroy
    EBitmap::~EBitmap()
    {
        DeleteObject(hBitmap);
        DeleteDC(bitmapHDC);
        SafeDeleteArray(pixels);
    }

    //get pixel
    EColor EBitmap::getPixel(EInt x, EInt y)
    {
        return pixels[y*pitch + x];
    }

    HINSTANCE GHInstance;

    HBITMAP     EGraphics::GBufferedHandle;
    HDC         EGraphics::GBufferedHDC;
    HBRUSH      EGraphics::GBgBrush;
    HPEN        EGraphics::GPen;
    HINSTANCE   EGraphics::GInstance;
    RECT        EGraphics::GBufferSize;
    DIBSECTION  EGraphics::GDIBSection;
    BYTE        *EGraphics::GDatas;
    EInt        EGraphics::GPitch;

    EFloat      *EGraphics::GZBuffer;

    //init draw system
    bool EGraphics::initGraphics(HINSTANCE hinstance)
    {
        GBufferedHDC = ::CreateCompatibleDC(NULL);

        BITMAPINFO info = { 0 };
        info.bmiHeader.biSize = sizeof(info.bmiHeader);
        info.bmiHeader.biWidth = SCREEN_WIDTH;
        info.bmiHeader.biHeight = -SCREEN_HEIGHT;
        info.bmiHeader.biPlanes = 1;
        info.bmiHeader.biBitCount = 32;
        info.bmiHeader.biCompression = BI_RGB;
        info.bmiHeader.biSizeImage = SCREEN_WIDTH * SCREEN_HEIGHT * 32 / 8;

        //create a space for texture and get the pointer
        void* pBits = NULL;
        GBufferedHandle = ::CreateDIBSection(GBufferedHDC, &info, DIB_RGB_COLORS, &pBits, NULL, 0);
        ::SelectObject(GBufferedHDC, GBufferedHandle);

        //dib.dsBm.bmBits points to hdib pixel
        ::GetObject(GBufferedHandle, sizeof(DIBSECTION), &GDIBSection);
        GDatas = (BYTE*)GDIBSection.dsBm.bmBits;
        GPitch = GDIBSection.dsBm.bmWidthBytes;

        //set buffer refresh zone
        ::SetRect(&GBufferSize, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

        GPen = ::CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
        ::SelectObject(GBufferedHDC, GPen);

        GBgBrush = ::CreateSolidBrush(RGB(0, 0, 0));
        ::SelectObject(GBufferedHDC, GBgBrush);

        //set text font
        HFONT hfnt = (HFONT)::GetStockObject(OEM_FIXED_FONT);
        ::SelectObject(GBufferedHDC, hfnt);

        //set text bg color
        ::SetBkMode(GBufferedHDC, TRANSPARENT);

        GZBuffer = new EFloat[SCREEN_WIDTH*SCREEN_HEIGHT];

        memset(GZBuffer, 0, sizeof(EFloat)*SCREEN_WIDTH*SCREEN_HEIGHT);

        return true;
    }

    //close draw system
    void EGraphics::shutdownGraphics()
    {
        ::DeleteObject(GPen);
        ::DeleteObject(GBgBrush);
        ::DeleteObject(GBufferedHandle);
        ::DeleteDC(GBufferedHDC);
    }

    //clear buffer, set as black
    void EGraphics::clearBuffer(const EColor &c)
    {
        ::FillRect(GBufferedHDC, &GBufferSize, GBgBrush);
        //reset z buffer
        //memset only works for int
        ::memset(GZBuffer, 0, sizeof(EFloat)*SCREEN_WIDTH*SCREEN_HEIGHT);
    }

    //draw a line inside buffer zone
    void EGraphics::drawLine(EInt x0, EInt y0, EInt x1, EInt y1, const EColor &c)
    {
        ::SelectObject(GBufferedHDC, GetStockObject(DC_PEN));
        ::SetDCPenColor(GBufferedHDC, RGB(c.r, c.g, c.b));

        ::MoveToEx(GBufferedHDC, x0, y0, NULL);
        ::LineTo(GBufferedHDC, x1, y1);
    }

    //draw string
    void EGraphics::drawString(const EString &str, EInt x, EInt y, const EColor &c)
    {
        ::SetTextColor(GBufferedHDC, RGB(c.r, c.g, c.b));
        ::TextOut(GBufferedHDC, x, y, str.c_str(), str.length());
    }

    void EGraphics::fillTriangle(EInt x0, EInt y0, EInt x1, EInt y1, EInt x2, EInt y2, const EColor &c)
    {

    }

    void EGraphics::enableSmoothingMode(EBool enable)
    {

    }

    //check z-buffer
    EBool EGraphics::checkZ(EInt x, EInt y, EFloat z)
    {
        EInt index = y * SCREEN_WIDTH + x;
        EFloat divZ = 1.0f / z;
        if (GZBuffer[index] > divZ)
            return false;

        GZBuffer[index] = divZ;
        return true;
    }

    //paint
    // check the z-buffer first then call this func
    void EGraphics::setPixel(EInt x, EInt y, const EColor &c)
    {
        BYTE* pSrcPix = GDatas + (GPitch * y);
        pSrcPix += x * 4;
        pSrcPix[0] = c.b;
        pSrcPix[1] = c.g;
        pSrcPix[2] = c.r;
        pSrcPix[3] = c.a;
    }

    EColor EGraphics::getPixel(EInt x, EInt y)
    {
        BYTE* pSrcPix = GDatas + (GPitch * y);
        pSrcPix += x * 4;
        return EColor(pSrcPix[2], pSrcPix[1], pSrcPix[0]);
    }

    //exchange the prepared buffer with the screen buffer, reset the cache
    void EGraphics::fillBuffer(HDC hdc)
    {
        ::BitBlt(hdc, 0, 0, SCREEN_HEIGHT, SCREEN_HEIGHT, GBufferedHDC, 0, 0, SRCCOPY);
    }
}