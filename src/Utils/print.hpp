#pragma once
#include <string>
#define FILE_NAME_ "config/logLevel.json"

enum LogLevel {
    DEBUG,
    WARNING,
    ERROR,
    TESTING,
    INFO
};


void  print(LogLevel logLevel, const char* format, ...);

void  log(LogLevel logLevel, const char* format, ...);

