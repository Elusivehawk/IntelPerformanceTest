#pragma once

#include "intelperf.h"

namespace intelperf
{
	struct BinaryNode
	{

	public:
		BinaryNode() {}
		
		BinaryNode(DataType v) : value(v) {}

		~BinaryNode()
		{
			delete left;
			delete right;

		}

		DataType value = 0;
		BinaryNode* left = nullptr;
		BinaryNode* right = nullptr;

	};

	BinaryNode* search(DataType value, BinaryNode* root);

	BinaryNode* insert(DataType value, BinaryNode* root);

	class BinaryTreeTest : public PerfTest
	{
	public:
		BinaryTreeTest() : PerfTest("Binary Tree") {}

		void PerfTest::runTest(DataType* data, uint64_t len)
		{
			BinaryNode* tree = nullptr;
			DataType nodeToFind = rand() % INTELPERF_DATATYPE_LIMIT;

			for (uint64_t i = 0; i < len; ++i)
			{
				tree = insert(data[i], tree);

			}

			BinaryNode* node = search(nodeToFind, tree);

			if (node->value == nodeToFind)
			{
				std::cout << "Found node " << nodeToFind << std::endl;

			}
			else
			{
				std::cout << "Could not find node " << nodeToFind << std::endl;

			}

			delete tree;

		}

	};

}
