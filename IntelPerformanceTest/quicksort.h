#pragma once

#include "intelperf.h"

namespace intelperf
{
	void quickSort(DataType* array, uint64_t startIndex, uint64_t endIndex);

	class QuickSortTest : public PerfTest
	{
	public:
		QuickSortTest() : PerfTest("QuickSort"){}

		void PerfTest::runTest(DataType* array, uint64_t len)
		{
			quickSort(array, 0, len - 1);

		}

	};

}