#include "bitchess.h"
#include <vector>
#include <stack>
#include <unordered_map> 
#include <unordered_set>
#include <iostream>
#include <fstream>
#include <time.h>

int main(int argc, const char *argv[]) {
	
	board::move lol(piece::w_pawn, "a2", "a4");

	lol.generateValidMoves();
	
	//lol.outputLegalMoves();

	std::cout << lol.isLegal() << std::endl;


	//lol.outputLegalMoves();
	board b;
	b.print();

	b.movePiece(lol);
	b.print();

	std::vector<board::move> kek;
	lol.returnLegal(kek, piece::b_quee, "d4");
	for (auto nask = kek.begin(); nask != kek.end(); nask++)
		std::cout << *nask << std::endl;

	std::cin.get();
    return 0;
}
