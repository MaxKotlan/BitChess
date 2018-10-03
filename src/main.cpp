#include "bitchess.h"

int main(int argc, const char *argv[]) {
	
	board b;
	b.print();
	std::cout << std::endl;
	b.addPiece(piece::w_quee, "d4");
	b.addPiece(piece::w_pawn, "d3");
	b.removePiece("a1");
	b.removePiece("e2");
	b.print();

	std::cin.get();
    return 0;
}
