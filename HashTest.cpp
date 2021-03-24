#include <cassert>
#include <iostream>
#include <gtest/gtest.h>
#include "Hash.h"

int hash_create(const float& val)
{
	return static_cast<int>(val);
}

TEST(HashTest, SimpleTest)
{
	HashMap<float> myHashMap(hash_create);
	for (int i = 0; i < 100; ++i)
		myHashMap.insert((float)i);
	float i = 0.0f;
	EXPECT_EQ(100, myHashMap.size());
	for (float f : myHashMap)
	{
		EXPECT_FLOAT_EQ(i, f);
		i += 1.0f;
	}
	EXPECT_EQ(100, myHashMap.size());
}

int main(int ac, char** av)
{
	::testing::InitGoogleTest(&ac, av);
	return RUN_ALL_TESTS();
}