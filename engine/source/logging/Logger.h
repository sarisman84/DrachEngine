#pragma once
#include <string_view>
#include <string>

#define CONSOLE_RED "\x1b[31m"
#define CONSOLE_YELLOW "\x1b[33m"
#define CONSOLE_GREEN "\x1b[32m"
#define CONSOLE_BLUE "x1b[34m"
#define CONSOLE_MAGENTA "\x1b[35m"
#define CONSOLE_CYAN "\x1b[36m"
#define CONSOLE_RESET "\x1b[0m"

void PrintLog(std::string_view&& aMessage, std::string_view&& aFile, const uint8_t aLine, const bool anErrorFlag);

#define LOG(x) PrintLog(std::string(x), std::string(__FILE__), __LINE__, false)
#define LOG_ERROR(x) PrintLog(std::string(x), std::string(__FILE__), __LINE__, true)