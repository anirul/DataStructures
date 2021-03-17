#include "Vector.h"
#include <cassert>
#include <iostream>
#include <gtest/gtest.h>

TEST(VectorTest, SimpleTest)
{
	Vector<int> myVector;
	myVector.reserve(1000);
	EXPECT_EQ(myVector.capacity(), 1000);
	for (int i = 0; i < 100; ++i)
		myVector.push_back(i);
	int i = 0;
	for (auto j : myVector)
	{
		EXPECT_EQ(j , i);
		i++;
	}
	EXPECT_EQ(myVector[14], myVector.at(14));
	EXPECT_EQ(42, myVector.at(42));
	EXPECT_EQ(100, myVector.size());
}

int main(int ac, char** av)
{
	::testing::InitGoogleTest(&ac, av);
	return RUN_ALL_TESTS();
}