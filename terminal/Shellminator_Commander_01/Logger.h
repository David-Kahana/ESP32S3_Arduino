#pragma once

#include <Stream.h>
#include <cstdio>
#include <cstdint>
#include <string>
#include <cstdarg>
#include <vector>

struct Color
{
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;
};

struct FB
{
    Color fgc;
    Color bgc;
};

class Attributes
{
  public:
    void resetAll()
    {
        char str[100];
        memset(str, 0, 100);
        sprintf(str, "%s%s%s", preamble, reset, ending);
        printf("%s", str);
    }

  public:
    const char preamble[6] = "\033[";
    const char seperator[2] = ";";
    const char ending[2] = "m";

    const char reset[2] = "0";  // (everything back to normal)
    const char bold[2] = "1";   // bright (often a brighter shade of the same colour)
    const char faint[2] = "2";  // faint decreased intensity, or dim	May be implemented as a light font weight like bold.

    const char underline[2] = "4";
    const char crossedOut[2] = "9";  // Crossed-out, or strike	Characters legible but marked as if for deletion. Not supported in Terminal.app.
    const char inverse[2] = "7";     // swap foreground and background colours
    const char boldOff[3] = "21";    // bright off
    const char underlineOff[3] = "24";
    const char inverseOff[3] = "27";

    const char blackFG[3] = "30";
    const char blackBG[3] = "40";
    const char redFG[3] = "31";
    const char redBG[3] = "41";
    const char greenFG[3] = "32";
    const char greenBG[3] = "42";
    const char yellowFG[3] = "33";
    const char yellowBG[3] = "43";
    const char blueFG[3] = "34";
    const char blueBG[3] = "44";
    const char magentaFG[3] = "35";
    const char magentaBG[3] = "45";
    const char cyanFG[3] = "36";
    const char cyanBG[3] = "46";
    const char whiteFG[3] = "37";
    const char whiteBG[3] = "47";
};

enum LogType
{
    NON = 0,
    DBG = 1,  // green
    INF = 2,  // white
    MSG = 3,  // blue
    USR = 4,  // magenta
    WRN = 5,  // yellow
    ERR = 6,  // red
    CRT = 7   // red
};

class Logger
{
  public:
    static inline std::vector<std::string> pres = { "\033[0m",                        // none
                                                    "\033[0;32mDEBUG: \033[0m",       // green
                                                    "\033[0;36mINFO: \033[0m",        // white
                                                    "\033[0;34mMESSAGE: \033[0m",     // blue
                                                    "\033[0;35mUSER: \033[0m",        // magenta
                                                    "\033[0;33mWARNING: \033[0m",     // yellow
                                                    "\033[0;31mERROR: \033[0m",       // red
                                                    "\033[0;31mCRITICAL: \033[0m" };  // red

    static void severityModify(uint8_t severity, std::string& pre)
    {
        switch (severity)
        {
            case 0:
                pre[2] = '2';  //faint
                break;
            case 1:
                pre[2] = '0';  //regular
                break;
            case 2:
                pre[2] = '1';  //bold
                break;
            default:
                pre[2] = '1';  //bold
        }
    }

    static void log(LogType type, uint8_t severity, const char* msg, ...)
    {
        std::string newMsg = pres[(int)type];
        severityModify(severity, newMsg);
        newMsg += msg;
        newMsg += "\r\n";

        //printf("%s", newMsg);
        va_list args;
        va_start(args, newMsg.c_str());
        vprintf(newMsg.c_str(), args);
        va_end(args);
    }

    static void log(const char* msg, ...)
    {
        std::string newMsg = pres[0];
        newMsg += msg;
        newMsg += "\r\n";
        va_list args;
        va_start(args, newMsg.c_str());
        vprintf(newMsg.c_str(), args);
        va_end(args);
    }

    static void log(Stream* stream, LogType type, uint8_t severity, const char* msg, ...)
    {
        std::string newMsg = pres[(int)type];
        severityModify(severity, newMsg);
        newMsg += msg;
        newMsg += "\r\n";

        //printf("%s", newMsg.c_str());
        va_list args;
        va_start(args, newMsg.c_str());
        stream->vprintf(newMsg.c_str(), args);
        va_end(args);
    }

    static void log(Stream* stream, const char* msg, ...)
    {
        std::string newMsg = pres[0];      
        newMsg += msg;
        newMsg += "\r\n";
        va_list args;
        va_start(args, newMsg.c_str());
        stream->vprintf(newMsg.c_str(), args);
        va_end(args);
    }
};