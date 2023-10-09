#include <iostream>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/daily_file_sink.h"

#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_DEBUG

void basic_logfile_example()
{
	try
	{
		auto logger = spdlog::basic_logger_mt("basic_logger", "logs/basic-log.txt");
	}
	catch (const spdlog::spdlog_ex& ex)
	{
		std::cout << "Log init failed: " << ex.what() << std::endl;
	}
}

void rotating_example()
{
	// Create a file rotating logger with 5mb size max and 3 rotated files
	auto max_size = 1048576 * 5;
	auto max_files = 3;
	auto logger = spdlog::rotating_logger_mt("some_logger_name",
		"logs/rotating.txt", max_size, max_files);
}

void daily_example()
{
	// Create a daily logger - a new file is created every day on 2:30am
	auto logger = spdlog::daily_logger_mt("daily_logger", "logs/daily.txt", 2,
		30);
}

int main()
{
	SPDLOG_INFO("Welcome to spdlog!");
	SPDLOG_TRACE("Trace");
	SPDLOG_DEBUG("Debug");
	SPDLOG_INFO("Support for floats {:03.2f}", 1.23456);
	SPDLOG_WARN("Easy padding in numbers like {:08d}", 12);
	SPDLOG_ERROR("Some error message with arg: {}", 1);
	SPDLOG_CRITICAL("Support for int: {0:d}; hex: {0:x}; oct: {0:o}; bin: {0:b}", 42);

	basic_logfile_example();
	rotating_example();
	daily_example();

	return 0;
}