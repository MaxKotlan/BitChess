#include "bitchess.h"

/*print binary of integer*/
void board::coordinate::printBinary() {
	for (int i = 7; i >= 0; i--)
		std::cout << ((cord >> i) & 1);
	std::cout << std::endl;
};

/*print hex of integer*/
void board::coordinate::printHex() {
	std::cout << std::hex << (int)cord << std::endl;
};
