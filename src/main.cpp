#include "bitchess.h"
#include <vector>
#include <stack>

int main(int argc, const char *argv[]) {
	
	board b;
	b.print();

	b.generateValidMoves();
	b.printValidMoves();

	board delta;
	delta.clear();
	for (uint8_t c = 0; c < 64; c++) {
		piece p = b.getPiece(c);
		if (p == piece::code::w_pawn)
			delta.addPiece(piece::code::w_pawn, c + 8);
	}
	delta.print();

	std::cout << "VECTOR: " << sizeof(std::vector<uint8_t>) << std::endl;
	std::cout << "STACK : " << sizeof(std::stack<uint8_t>) << std::endl;


	std::cin.get();
    return 0;
}
