#include <iostream>
#include "../utilities/include/TestUtility.h"

int main()
{
	std::cout << "Server Launched" << std::endl;
	
	TestUtility *t = new TestUtility(7);

	std::cout << t->GetValue10() << std::endl;

	return 0;
}
