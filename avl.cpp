#include "stdafx.h"
#include <iostream>

template <typename T>
class AvlTree
{
	T key;
	int height;
	AvlTree *left;
	AvlTree *right;

	static int getHeight(AvlTree *tree)
	{
		if (tree)
			return tree->height;
		return 0;
	}

	AvlTree* makeRightSmallRotate(AvlTree *tree)
	{
		AvlTree *newTree = tree->left;
		tree->left = newTree->right;
		newTree->right = tree;
		tree->fixNodeHeight();
		newTree->fixNodeHeight();

		return newTree;
	}


	AvlTree* makeLeftSmallRotate(AvlTree *tree)
	{

		AvlTree *newTree = tree->right;
		tree->right = newTree->left;
		newTree->left = tree;
		tree->fixNodeHeight();
		newTree->fixNodeHeight();

		return newTree;
	}

	int getBalanceFactor()
	{
		return getHeight(right) - getHeight(left);
	}

	void fixNodeHeight()
	{
		auto leftHeight = getHeight(left);
		auto rightHeight = getHeight(right);
		height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
	}

	AvlTree *balanceTree()
	{
		fixNodeHeight();
		if (getBalanceFactor() == 2) //big left rotate 
		{
			if (right->getBalanceFactor() < 0)
				right = makeRightSmallRotate(right);
			return makeLeftSmallRotate(this);
		}

		if (getBalanceFactor() == -2) // big right rotate
		{
			if (left->getBalanceFactor() > 0)
				left = makeLeftSmallRotate(left);
			return makeRightSmallRotate(this);
		}
		return this;
	}

	AvlTree *findMinimalKeyInSubtree()
	{
		return left ? left->findMinimalKeyInSubtree() : this;
	}

	AvlTree *removeMinimalSubtree()
	{
		if (!left)
			return right;
		left = left->removeMinimalSubtree();
		balanceTree();
	}

public:
	AvlTree(T key)
	{
		this->key = key;
		height = 1;
	}

	AvlTree *removeTree(T key)
	{
		if (key < this->key)
			left = left->removeTree(key);
		else if (this->key < key)
			right = right->removeTree(key);
		else
		{
			AvlTree *minInRightSubtree = right->findMinimalKeyInSubtree();
			minInRightSubtree->right = right->removeMinimalSubtree();
			minInRightSubtree->left = left;

			delete this;
			return minInRightSubtree->balanceTree();
		}
	}


	AvlTree* insertTree(T key)
	{
		if (key >= this->key) 
		{
			if (!right)
				right = new AvlTree(key);
			else
				right->insertTree(key);
		}
		else 
		{
			if (!left)
				left = new AvlTree(key);
			else
				left->insertTree(key);
		}
		return this->balanceTree();
	}

	void traversal()
	{
		if (left)
			left->traversal();
		std::cout << key << std::endl;
		if (right)
			right->traversal();
	}
};

int main(int argc, char *argv[])
{
	AvlTree<double> *tree = new AvlTree<double>(2);
	tree = tree->insertTree(21);
	tree = tree->insertTree(28);
	tree = tree->insertTree(12);
	tree = tree->insertTree(228);
	tree = tree->insertTree(1);
	tree = tree->insertTree(3);
	tree = tree->insertTree(2);

	tree->traversal();
}