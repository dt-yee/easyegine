#pragma once
#include "ECommon.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <stdarg.h>
#include <Windows.h>
#include <ctime>

namespace E3D
{
    //global file stream
    extern std::ofstream * GLogStream;
    
    //init Log sys
    bool InitLog(const EString &fileName);

    //record info, use InitLog to initialize the Log, use CloseLog to close
    void Log(const EChar *string, ...);

    void CloseLog();

    //random number with range
    inline EInt RandomInt(EInt from = 0, EInt to = 10) 
    {
        EInt ran = rand() % (to - from + 1) + from;
        return ran;
    }

    //integer to string
    inline EString IntToString(EFloat num)
    {
        std::stringstream ss;
        ss << num;
        EString res;
        ss >> res;
        return res;
    }

    //string to integer
    inline EInt StringToInt(const EString &str)
    {
        return atoi(str.c_str());
    }

    //string to float
    inline EFloat StringToFloat(const EString &str)
    {
        return (EFloat)atof(str.c_str());
    }

    //to string
    inline EWString ToEWString(const EString &str)
    {
        int wcsLen = ::MultiByteToWideChar(CP_ACP, NULL, str.c_str(), str.size(), NULL, 0);
        WCHAR *tString = new WCHAR[wcsLen + 1];

        ::MultiByteToWideChar(CP_ACP, NULL, str.c_str(), str.size(), tString, wcsLen);
        tString[wcsLen] = '\0';

        return EWString(tString);
    }

    //float equal
    inline EBool EqualFloat(EFloat l, EFloat r)
    {
        return abs(l - r) <= EPSILON_E6;
    }

    //get filename from path
    inline EString GetNameFromPath(const EString &path)
    {
        std::size_t begin = path.find_last_of("\\/");
        std::size_t end = path.find_last_of(".");

        if (begin == EString::npos)
            begin = -1;
        return path.substr(begin + 1, end - begin - 1);
    }

    //remove space char at both ends of a string
    inline EString Trim(const EString &msg)
    {
        const static EString SPACE_CHAR = "\t\f\v\n\r";
        std::size_t begin = msg.find_first_not_of(SPACE_CHAR);
        
        //empty string
        if (begin > msg.length())
            return EString();
        EString result = msg.substr(begin);
        std::size_t end = result.find_last_not_of(SPACE_CHAR);
        if (end != EString::npos)
            end++;
        return result.substr(0, end);
    }

}