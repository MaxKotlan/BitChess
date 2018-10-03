#include "bitchess.h"

int main(int argc, const char *argv[]) {
	
	board b;
	b.print();

	b.addPiece(piece::w_quee, "d4");
	b.addPiece(piece::w_pawn, "d3");
	b.print();

	std::cin.get();
    return 0;
}
