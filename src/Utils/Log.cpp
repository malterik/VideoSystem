#include "Log.hpp"
#include <cstdio>
#include <cstdarg>
#include <cstring>


Log::Log() 
{
}

void Log::print(LogLevel logLevel, const char* format, ...) {
    char color[200];
    if(logLevel == ERROR) {
        std::strcpy(color, "\e[31m"); 
        std::strcat(color, "\e[1mERROR: \e[21m");
        std::strcat(color, format);
        std::strcat(color, "\033[0m");
        std::strcat(color, "\r\n");
    } else if(logLevel == WARNING) {
        std::strcpy(color, "\e[33;1mWARNING: \e[0m");
        std::strcat(color, format);
        std::strcat(color, "\033[0m");
        std::strcat(color, "\r\n");
    } else if(logLevel == INFO) {
        std::strcpy(color, "\e[32m"); 
        std::strcat(color, "\e[1mINFO: \e[21m");
        std::strcat(color, format);
        std::strcat(color, "\033[0m");
        std::strcat(color, "\r\n");
    }
    va_list args; 
    va_start( args, format);
    vprintf(color, args);
    va_end( args );
}
