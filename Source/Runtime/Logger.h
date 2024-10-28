#pragma once
#include <string_view>
#include "fmt/core.h"
#include "fmt/os.h"
#include "fmt/color.h"
#include <chrono>
#include <fmt/chrono.h>


// Define the single LOG macro with conditional compilation
#ifdef DEBUG
	#define LOG(level, message, ...) LogHandler::Get().Log(level, message, ##__VA_ARGS__)
#else
	#define LOG(level, message, ...) // No-op in release builds
#endif


#define INFO 0
#define SUCCESS 1
#define WARNING 2
#define ERROR 3
#define FATAL 4




class LogHandler
{
public:

	inline static LogHandler& Get()
	{
		static LogHandler handler{};
		return handler;
	}

	template <typename... Args>
	inline static void print(std::string_view message, Args... args)
	{
		fmt::print((message), args...);
		fmt::print("\n");
	}


	template <typename... Args>
	inline static void Log(int type,std::string_view message, Args... args)
	{
		PrintTime();
		switch (type)
		{
			case FATAL:
			{
				fmt::print(fg(fmt::color::crimson) | fmt::emphasis::bold,
					"[FATAL]   ");
				break;
			}
			case ERROR:
			{
				fmt::print(fg(fmt::color::crimson),
					"[ERROR]   ");
				break;
			}
			case WARNING:
			{
				fmt::print(fg(fmt::color::yellow),
					"[WARNING] ");
				break;
			}
			case SUCCESS:
			{
				fmt::print(fg(fmt::color::light_green),
					"[SUCCESS] ");
				break;
			}
			case INFO:
			{
				fmt::print(fg(fmt::color::white),
					"[INFO]    ");
				break;
			}
		}		
		
		print(message, args...);

		if (type == FATAL)
		{
			abort();
		}
	}


	inline static void PrintTime()
	{
		std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
		auto time_point = now - LogHandler::Get().start_time;
		fmt::print("[{:%M:%S}]", time_point);
	}

	void SetTime()
	{
		start_time = std::chrono::system_clock::now();
	}

	std::chrono::time_point<std::chrono::system_clock> start_time;
};
