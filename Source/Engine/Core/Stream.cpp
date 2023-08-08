#include "Stream.h"
#include <Windows.h>

namespace kiko
{
	void debug_stream::write(bool v) { char s[32]; sprintf_s(s, 32, "%d", v); OutputDebugStringA(s); }
	void debug_stream::write(int v) { char s[32]; sprintf_s(s, 32, "%d", v); OutputDebugStringA(s); }
	void debug_stream::write(float v) { char s[32]; sprintf_s(s, 32, "%f", v); OutputDebugStringA(s); }
	void debug_stream::write(double v) { char s[32]; sprintf_s(s, 32, "%f", v); OutputDebugStringA(s); }
	void debug_stream::write(char v) { char s[32]; sprintf_s(s, 32, "%c", v); OutputDebugStringA(s); }
	void debug_stream::write(const std::string& v) { OutputDebugStringA(v.c_str()); }
}
