#include "Logger.h"
#include "FileIO.h"
#include <Windows.h> 
#include <string>
#include <iostream>
#include <sstream>
#include <cstdarg>
#include <cstdio>

namespace kiko
{
	Logger g_logger(LogLevel::Info, &std::cout, "log.txt");

	bool Logger::Log(LogLevel level, const char* filename, int line)
	{
		if (level < m_level) return false;

		switch (level)
		{
		case LogLevel::Info:
			*this << "INFO: ";
			break;
		case LogLevel::Warning:
			*this << "WARNING: ";
			break;
		case LogLevel::Error:
			*this << "ERROR: ";
			break;
		case LogLevel::Assert:
			*this << "ASSERT: ";
			break;
		default:
			break;
		}

		*this << getFileName(filename) << "(" << line << ") ";

		return true;
	}
}
