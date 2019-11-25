
#include "binarytree.h"

using namespace intelperf;

BinaryNode* intelperf::search(DataType value, BinaryNode* root)
{
	if (!root)
	{
		return nullptr;
	}

	if (root->value > value)
	{
		return intelperf::search(value, root->left);
	}

	if (root->value < value)
	{
		return intelperf::search(value, root->right);
	}

	return root;
}

BinaryNode* intelperf::insert(DataType value, BinaryNode* root)
{
	if (!root)
	{
		return new BinaryNode(value);
	}

	if (root->value > value)
	{
		root->left = intelperf::insert(value, root->left);

	}

	if (root->value < value)
	{
		root->right = intelperf::insert(value, root->right);

	}

	return root;
}

