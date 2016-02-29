#pragma once

#include <string>

enum LogLevel {
    DEBUG,
    WARNING,
    ERROR,
    TESTING,
    INFO
};


void  print(LogLevel logLevel, const char* format, ...);

void  log(LogLevel logLevel, const char* format, ...);

