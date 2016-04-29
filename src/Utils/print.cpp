#include "print.hpp"
#include <cstdio>
#include <cstdarg>
#include <cstring>
#include "../json/json.hpp"
#include <iostream>
#include <fstream>

#define FILE_NAME_ "config/logLevel.json"
using json = nlohmann::json;

void readConfig();

bool show_error_;
bool show_warning_;
bool show_info_;
bool show_testing_;
bool show_debug_;

void readConfig() {
  std::string line;
  json logConfig;
  std::ifstream configFile (FILE_NAME_);
  if (configFile.is_open()) {
    std::string str((std::istreambuf_iterator<char>(configFile)),
                     std::istreambuf_iterator<char>());
    logConfig = json::parse(str);
    show_error_ = logConfig["show_error"];
    show_warning_ = logConfig["show_warning"];
    show_info_ = logConfig["show_info"];
    show_testing_ = logConfig["show_testing"];
    show_debug_ = logConfig["show_debug"];

    configFile.close();
  } else std::cout << "Unable to open log config file" << std::endl;
}

void print(LogLevel logLevel, const char* format, ...) {
  readConfig();
  char color[200];
  if(logLevel == ERROR && show_error_) {
    std::strcpy(color, "\e[31m");
    std::strcat(color, "ERROR: ");
    std::strcat(color, "\033[0m");
    std::strcat(color, format);
    std::strcat(color, "\r\n");
  } else if(logLevel == WARNING && show_warning_) {
    std::strcpy(color, "\e[33mWARNING: ");
    std::strcat(color, "\033[0m");
    std::strcat(color, format);
    std::strcat(color, "\r\n");
  } else if(logLevel == INFO && show_info_) {
    std::strcpy(color, "\e[32m");
    std::strcat(color, "INFO: ");
    std::strcat(color, "\033[0m");
    std::strcat(color, format);
    std::strcat(color, "\r\n");
  } else if(logLevel == DEBUG && show_debug_) {
    std::strcpy(color, "\e[34m");
    std::strcat(color, "DEBUG: ");
    std::strcat(color, "\033[0m");
    std::strcat(color, format);
    std::strcat(color, "\r\n");
  } else if(logLevel == TESTING && show_testing_) {
    std::strcpy(color, "\e[35m");
    std::strcat(color, "TESTING: ");
    std::strcat(color, "\033[0m");
    std::strcat(color, format);
    std::strcat(color, "\r\n");
  }
  va_list args;
  va_start( args, format);
  vprintf(color, args);
  va_end( args );
}
