#include "EUtil.h"

namespace E3D
{
    std::ofstream *GLogStream = NULL;

    bool InitLog(const EString &fileName)
    {
        if (GLogStream = NULL)
        {
            GLogStream = new std::ofstream();
            GLogStream->open(fileName.c_str());
            if (GLogStream->good())
                return true;
            return false;
        }
    }

    void Log(const EChar *string, ...)
    {
        if (GLogStream == NULL)
            return;
        EChar buffer[256];

        if (!string || !GLogStream)
            return;

        //get va list from stack
        va_list arglist;
        va_start(arglist, string);
        vsprintf(buffer, string, arglist);
        va_end(arglist);

        EString info(buffer);

        *GLogStream << info << std::endl;
        GLogStream->flush();
    }

    void ClostLog()
    {
        GLogStream->close();
        SafeDelete(GLogStream);
    }
}