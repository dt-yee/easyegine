#pragma

#include "ECommon.h"
#include <Windows.h>

namespace E3D
{
    extern HINSTANCE GHInstance;

    //graph encapsulation, GDI+
    class EBitmap
    {
    public:
        EInt width, height;
        EColor *pixels;
        EInt pitch;
        EBool valid;

        EBitmap(const EString &filename);
        ~EBitmap();

        inline EString getName() const { return name; }
        inline bool isValid() const { return valid; }
        EColor getPixel(EInt x, EInt y);
        inline EInt getHeight() const { return height; }
        inline EInt getWidth() const { return width; }

    private:
        EString name;

        HBITMAP hBitmap;
        BITMAP bitmap;
        HDC bitmapHDC;
    };

    class EGraphics
    {
    public:
        //init the graphics system
        static bool initGraphics(HINSTANCE hinstance);

        //shut down
        static void shutdownGraphics();

        //z-test, pass then call set pixel
        static EBool checkZ(EInt x, EInt y, EFloat z);
        
        static void setPixel(EInt x, EInt y, const EColor &c);

        static EColor getPixel(EInt x, EInt y);
        
        //draw line
        static void drawLine(EInt x0, EInt y0, EInt x1, EInt y1, const EColor &c);

        //draw string
        static void drawString(const EString &str, EInt x, EInt y, const EColor &c = EColor(255, 255, 255));

        //fill triangle
        static void fillTriangle(EInt x0, EInt y0, EInt x1, EInt y1, EInt x2, EInt y2, const EColor &c = EColor(255, 255, 255));

        //smooth mode
        static void enableSmoothingMode(EBool enable);

        //clear buffer, set as black
        static void clearBuffer(const EColor &c = EColor());

        //exchange the two buffers
        static void fillBuffer(HDC hdc);

        //get screen width
        static EInt getScreenWidth() { return SCREEN_WIDTH; }
        //get screen height
        static EInt getScreenHeight() { return SCREEN_HEIGHT; }

    private:
        static HBITMAP      GBufferedHandle;
        static HDC          GBufferedHDC;
        static HBRUSH       GBgBrush;
        static HPEN         GPen;
        static HINSTANCE    GInstance;

        static BYTE         *GDatas;
        static EInt         GPitch;

        static DIBSECTION   GDIBSection;

        static RECT         GBufferSize;

        static EFloat       *GZBuffer;
    };
}