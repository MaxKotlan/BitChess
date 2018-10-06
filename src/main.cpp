#include "bitchess.h"
#include <vector>
#include <stack>

int main(int argc, const char *argv[]) {
	
	board b;
	//b.clear();
	//b.addPiece(piece::code::w_knig, "h4");
	for (int k = 1; k < 7; k++) {
		for (int i = 0; i < 64; i++) {
			b.clear();
			b.addPiece(k, i);

			//b.print();

			b.generateValidMoves();
			//b.printValidMoves();
			//b.printMoveMap();
			//std::cout << i << std::endl;

		}
	}
	std::cout << "Total Legal Moves: " << b.validMoveSize() << std::endl;


	std::cin.get();
    return 0;
}
