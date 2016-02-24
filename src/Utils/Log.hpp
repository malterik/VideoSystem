#pragma once

enum LogLevel {
    DEBUG,
    WARNING,
    ERROR,
    TESTING,
    INFO
};

class Log {

public:
    Log();
    static void  print(LogLevel logLevel, const char* format, ...);
    static void  log(LogLevel logLevel, const char* format, ...);

private:
    
};
