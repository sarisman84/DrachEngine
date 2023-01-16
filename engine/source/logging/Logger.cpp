#include "Logger.h"
#include <iostream>
#include <string>
#include <Windows.h>
void PrintLog(std::string_view&& aMessage, std::string_view&& aFile, const uint8_t aLine, const bool anErrorFlag)
{
	size_t pos = aFile.find_last_of("\\");
	auto fileName = aFile.substr(pos + 1);
	auto line = std::string("Line ") + std::to_string(aLine);

	auto begin = anErrorFlag ? "[ERROR]" : "[LOG]";

	auto message = std::string(begin) + "(" + std::string(fileName.data()) + " - " + line + ") : " + aMessage.data() + "\n";
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, anErrorFlag ? (FOREGROUND_RED | FOREGROUND_INTENSITY) : (FOREGROUND_GREEN | FOREGROUND_INTENSITY));
	printf(message.c_str());
	SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY));
}
