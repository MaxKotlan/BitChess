#include <iostream>
#include "tests.h"

int main(int argc, char* argv[])
{
	std::cout << "-------------------STARTING TESTS-------------------" << std::endl;
	testboard();
	testcoordinate();
	std::cout << "--------------------ENDING TESTS--------------------" << std::endl;
}
