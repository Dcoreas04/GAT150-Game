#pragma once
#include "Stream.h"
#include <string>
#include <cassert>

#ifdef _DEBUG
#define INFO_LOG(message) { if (kiko::g_logger.Log(kiko::LogLevel::Info, __FILE__, __LINE__)) {kiko::g_logger << message << "\n";} }
#define WARNING_LOG(message) { if (kiko::g_logger.Log(kiko::LogLevel::Warning, __FILE__, __LINE__)) {kiko::g_logger << message << "\n";} }
#define ERROR_LOG(message) { if (kiko::g_logger.Log(kiko::LogLevel::Error, __FILE__, __LINE__)) {kiko::g_logger << message << "\n";} }
#define ASSERT_LOG(condition, message) { if (!condition && kiko::g_logger.Log(kiko::LogLevel::Assert, __FILE__, __LINE__)) {kiko::g_logger << message << "\n";} assert(condition) }
#else 
#define INFO_LOG(message)	{}
#define WARNING_LOG(message)	{}
#define ERROR_LOG(message)	{}
#define ASSERT_LOG(condition, message)	{}
#endif

namespace kiko
{
	enum class LogLevel
	{
		Info,
		Warning,
		Error,
		Assert
	};

	class Logger
	{
	public:
		Logger(LogLevel loglevel, std::ostream* stream, const std::string& filename) :
			m_level{ loglevel },
			m_ostream{ stream }
		{
			if (!filename.empty()) m_fstream.open(filename);
		};
		~Logger()
		{
			if (m_fstream.is_open()) m_fstream.close();
		}

		void SetLevel(LogLevel loglevel) { m_level = loglevel; }
		bool Log(LogLevel loglevel, const char* filename, int line);

		template<typename T>
		Logger& operator << (T value);

	private:
		LogLevel m_level;
		std::ostream* m_ostream = nullptr;
		std::ofstream m_fstream;
	};

	extern Logger g_logger;

	template<typename T>
	inline Logger& Logger::operator<<(T value)
	{
		// TODO: insert return statement here
		if(m_ostream) *m_ostream << value;
		if (m_fstream.is_open())
		{
			m_fstream << value;
			m_fstream.flush();
		}

		return *this;
	}
}