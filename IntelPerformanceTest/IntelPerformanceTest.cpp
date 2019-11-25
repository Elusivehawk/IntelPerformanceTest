
#include <cstring>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

#include "intelperf.h"
#include "quicksort.h"
#include "countsort.h"
#include "binarytree.h"

#define INTEL_PERF_TEST_VERSION "1.0"
#define DATA_SET_SIZE (1000000)
#define TEST_RUN_COUNT (10)

using namespace intelperf;

void keyToExit()
{
	std::cout << "Enter any key to exit\n";

	char exit;

	std::cin >> exit;

	std::cout << exit;

}

void printHelp()
{
	std::cout << "Run with --help (e.g. \"intelperf --help\" to see this\n";
	std::cout << "Run with various characters (e.g. \"intelperf qcb\" to run various tests\n";
	std::cout << "\t\'q\' adds the QuickSort test\n";
	std::cout << "\t\'c\' adds the Counting Sort test\n";
	std::cout << "\t\'b\' adds the Binary Tree (build + search) test\n";

}

int main(int argc, char** argv)
{
	std::cout << "Welcome to Elusivehawk's Intel(C) Performance Tester v" << INTEL_PERF_TEST_VERSION << std::endl;
	std::cout << "This program is intended to be a simple benchmarking tool for testing Intel's C++ compiler.\n";
	std::cout << "Use of this program by any means grants zero warranty. Use at your own risk!\n";
	std::cout << "You can get the latest source code here: https://github.com/Elusivehawk/IntelPerformanceTest \n";
	std::cout << "===== Running with data set size: " << DATA_SET_SIZE << " =====\n";

	std::vector<PerfTest*> tests;

	char* file = nullptr;

	for (int op = 0; op < argc - 1; ++op)
	{
		if (argv[op] == "--help")
		{
			printHelp();
			keyToExit();

			return 0;
		}
		
		if (argv[op] == "-f")
		{
			file = argv[op++];

		}

	}

	if (argc < 2)
	{
		std::cout << "Running all the tests\n";

		tests.push_back(new QuickSortTest());
		tests.push_back(new CountingSortTest());
		tests.push_back(new BinaryTreeTest());

	}
	else
	{
		char* options = argv[1];

		if (options[0] != '-')
		{
			std::cout << "Options found: " << options << std::endl;

			for (size_t i = 0; i < strlen(options); ++i)
			{
				switch (options[i])
				{
				case 'q': tests.push_back(new QuickSortTest()); break;
				case 'c': tests.push_back(new CountingSortTest()); break;
				case 'b': tests.push_back(new BinaryTreeTest()); break;
				default: std::cout << "Unknown test: " << options[i] << std::endl;
				}

			}

		}

	}

	if (tests.size() == 0)
	{
		std::cout << "Could not run any tests; Be sure you ran me with the correct flags (run with --help for help)\n";
		
		return -1;
	}

	DataType* data = new DataType[DATA_SET_SIZE];
	DataType* dataBackup = new DataType[DATA_SET_SIZE];

	std::fstream dataFile(file, std::ios::binary);

	if (file && dataFile.good())
	{
		dataFile.read((char*)data, DATA_SET_SIZE * sizeof(DataType));
		dataFile.close();
		std::memcpy(dataBackup, data, DATA_SET_SIZE * sizeof(DataType));

	}
	else
	{
		std::fstream dataIn("testData.txt", std::ios::binary);

		for (long i = 0; i < DATA_SET_SIZE; ++i)
		{
			data[i] = (rand() % INTELPERF_DATATYPE_LIMIT);
			dataBackup[i] = data[i];

		}

		dataIn.write((const char*)data, DATA_SET_SIZE * sizeof(DataType));
		dataIn.close();

		std::cout << "Random values generated; Run again with -f \"testData.txt\" to reproduce your results\n";

	}
	
	for (PerfTest* test : tests)
	{
		std::cout << "Running test: " << test->name << std::endl;

		Stopwatch timer;
		double totalTime = 0;

		for (int i = 0; i < TEST_RUN_COUNT; ++i)
		{
			std::cout << "Test #" << i + 1 << std::endl;
			//Ensure we're always using raw data and not processed
			//e.g. if we sorted the only data array, then the following tests would be useless
			std::memcpy(data, dataBackup, DATA_SET_SIZE * sizeof(DataType));

			timer.start();
			test->runTest(data, DATA_SET_SIZE);
			timer.stop();

			//Done so that certain compilers don't optimize out the tests themselves (clever bastards)
			std::cout << "First element: " << data[0] << ", ";
			std::cout << "last element: " << data[DATA_SET_SIZE - 1] << std::endl;
			std::cout << "Time: " << timer.timeMS() << " ms\n";

			totalTime += timer.timeMS();

		}

		double avgTime = totalTime / TEST_RUN_COUNT;

		std::cout << test->name << " test completed; Average time: " << avgTime << " ms\n";

	}

	std::cout << "Tests complete\n";
	
	keyToExit();

	return 0;
}
