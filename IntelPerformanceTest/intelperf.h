#pragma once

#include <chrono>
#include <iostream>
#include <random>
#include <stdint.h>

#define INTELPERF_DATATYPE_LIMIT (0x8000)

using namespace std::chrono;

namespace intelperf
{
	typedef uint16_t DataType;

	class PerfTest
	{
	public:
		const char* name;

		PerfTest() : PerfTest("glitchy boi") {}

		PerfTest(const char* testName)
		{
			name = testName;

		}

		virtual void runTest(DataType* data, uint64_t len) = 0;
	};

	class Stopwatch
	{
	private:
		high_resolution_clock::time_point begin, end;

	public:
		void start()
		{
			begin = std::chrono::high_resolution_clock::now();

		}

		void stop()
		{
			end = high_resolution_clock::now();

		}

		double timeMS()
		{
			return (1.0 * duration_cast<nanoseconds>(end - begin).count()) / 1000000.0;
		}

	};

}