
#include "quicksort.h"

using namespace intelperf;

void swapValues(DataType* array, uint64_t firstIndex, uint64_t secondIndex)
{
	DataType tmp = array[firstIndex];
	array[firstIndex] = array[secondIndex];
	array[secondIndex] = tmp;

}

uint64_t partition(DataType* array, uint64_t startIndex, uint64_t endIndex)
{
	DataType pivotValue = array[endIndex];
	uint64_t i = startIndex;


	for (uint64_t j = startIndex; j < endIndex; ++j)
	{
		if (array[j] <= pivotValue)
		{
			swapValues(array, i, j);
			++i;

		}

	}

	swapValues(array, i, endIndex);

	return i;
}

void intelperf::quickSort(DataType* array, uint64_t startIndex, uint64_t endIndex)
{
	if (startIndex >= endIndex)
	{
		return;
	}

	uint64_t pivot = partition(array, startIndex, endIndex);
	quickSort(array, startIndex, pivot - 1);
	quickSort(array, pivot + 1, endIndex);

}
