#include <cassert>
#include <iostream>
#include <gtest/gtest.h>
#include "List.h"

TEST(ListTest, SimpleTest)
{
	List<float> myList;
	for (int i = 0; i < 100; ++i)
		myList.push_back((float)i);
	float i = 0.0f;
	EXPECT_EQ(100, myList.size());
	for (float f : myList)
	{
		EXPECT_FLOAT_EQ(i, f);
		i += 1.0f;
	}
	EXPECT_FLOAT_EQ(0.0f, myList.front());
	EXPECT_FLOAT_EQ(99.0f, myList.back());
	EXPECT_EQ(100, myList.size());
}

int main(int ac, char** av)
{
	::testing::InitGoogleTest(&ac, av);
	return RUN_ALL_TESTS();
}