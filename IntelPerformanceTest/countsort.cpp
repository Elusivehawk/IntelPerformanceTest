
#include "countsort.h"

using namespace intelperf;

void intelperf::countingSort(DataType* data, uint64_t len)
{
	DataType* sorted = new DataType[len];
	DataType k = data[0];
	uint64_t* count = new uint64_t[INTELPERF_DATATYPE_LIMIT]{ 0 };

	//Step 1

	for (uint64_t i = 0; i < len; ++i)
	{
		count[data[i]] += 1;

		if (data[i] > k)
		{
			k = data[i];

		}

	}

	//Step 2

	for (uint32_t i = 1; i <= k; ++i)
	{
		count[i] += count[i - 1];

	}

	//Step 3

	for (uint32_t i = 0; i < len; ++i)
	{
		sorted[count[data[i]] - 1] = data[i];
		count[data[i]] -= 1;

	}

	//Step 4

	memcpy(data, sorted, len * sizeof(DataType));

	delete[] sorted;
	delete[] count;

}
