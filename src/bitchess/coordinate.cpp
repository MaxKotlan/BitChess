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

std::string board::coordinate::getDisplayCoordinates(){
	std::string c;
	c.push_back((cord % 8) + 'a');
	c.push_back((cord / 8) + '1');
	return c;
}


bool board::coordinate::operator == (const board::coordinate& rhs) {
	return (cord == rhs.cord);
}

bool board::coordinate::operator != (const board::coordinate& rhs) {
	return !(*this == rhs);
}
