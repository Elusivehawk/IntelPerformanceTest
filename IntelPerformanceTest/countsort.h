#pragma once

#include "intelperf.h"

namespace intelperf
{
	void countingSort(DataType* data, uint64_t len);

	class CountingSortTest : public PerfTest
	{
	public:
		CountingSortTest() : PerfTest("Counting Sort") {}

		void PerfTest::runTest(DataType* data, uint64_t len)
		{
			countingSort(data, len);

		}

	};

}