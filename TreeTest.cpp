#include <cassert>
#include <iostream>
#include <gtest/gtest.h>
#include <random>
#include "Tree.h"

TEST(TreeTest, SimpleTest)
{
	std::random_device rd;
	std::mt19937 e2(rd());
	std::uniform_real_distribution<> dist(0, 100);
	Tree<float> myTree;
	for (int i = 0; i < 5; ++i)
		myTree.insert((float)dist(e2));
	myTree.print();
	float g = std::numeric_limits<float>::min();
	for (auto it = myTree.begin(); it != myTree.end(); ++it)
	{
		EXPECT_LE(g, *it);
		g = *it;
	}
	g = std::numeric_limits<float>::min();
	for (auto f : myTree)
	{
		EXPECT_LE(g, f);
		g = f;
	}
}

int main(int ac, char** av)
{
	::testing::InitGoogleTest(&ac, av);
	return RUN_ALL_TESTS();
}