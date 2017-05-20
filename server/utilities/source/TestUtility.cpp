//
// Created by 陈齐斌 on 20/05/2017.
//

#include "TestUtility.h"
#include <iostream>

TestUtility::TestUtility(int set)
{
	std::cout << "TestUtility Constructor" << std::endl;

	value = set;
}

int TestUtility::GetValue10() const
{
	return value * 10;
}
