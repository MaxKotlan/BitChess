#include "tests.h"
#include "bitchess.h"

#include <cassert>

void testboard() {
	std::cout << "------Testing Board Size ------" << std::endl;
	{
		board b;
		assert(sizeof(b) == sizeof( uint32_t) *8);
		assert(sizeof(b) == 32);
	}
	{
		board b, c;
		
	}
}