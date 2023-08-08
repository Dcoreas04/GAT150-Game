#pragma once
#include <string>
#include <iostream>
#include <fstream>

namespace kiko
{
	class stream
	{
	public:
		virtual ~stream() {}

		virtual void write(bool v) = 0;
		virtual void write(int v) = 0;
		virtual void write(float v) = 0;
		virtual void write(double v) = 0;
		virtual void write(char v) = 0;
		virtual void write(const std::string& v) = 0;
	};

	class output_stream : public stream
	{
	public:
		output_stream(std::ofstream& output, const std::string& filename) : m_stream{ output }
		{
			output.open(filename);
		}
		output_stream(std::ostream& output) : m_stream{ output } {}

		void write(bool v) override { m_stream << v; }
		void write(int v) override { m_stream << v; }
		void write(float v) override { m_stream << v; }
		void write(double v) override { m_stream << v; }
		void write(char v) override { m_stream << v; }
		void write(const std::string& v) override { m_stream << v; }

		template <typename T>
		std::ostream& operator << (T value)
		{
			write(value);
			return m_stream;
		}

	private:
		std::ostream& m_stream;
	};

	class debug_stream : public stream
	{
	public:
		void write(bool v) override;
		void write(int v) override;
		void write(float v) override;
		void write(double v) override;
		void write(char c) override;
		void write(const std::string& v) override;

		template <typename T>
		debug_stream& operator << (T value)
		{
			write(value);
			return *this;
		}
	};
}