#include "bitchess.h"

int main(int argc, const char *argv[]) {
	
	board b;
	b.print();

	//std::cout << piece::getHumanReadable(b.getPiece("a1")).c_str() << std::endl;

	std::cin.get();
    return 0;
}
