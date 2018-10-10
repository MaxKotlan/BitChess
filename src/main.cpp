#include "bitchess.h"
#include <vector>
#include <stack>
#include <unordered_map> 
#include <unordered_set>
#include <iostream>
#include <fstream>
#include <time.h>

int main(int argc, const char *argv[]) {
	
	board::move lol(piece::w_pawn, "d2", "d4");

	lol.generateValidMoves();
	
	//lol.outputLegalMoves();

	std::cout << lol.isLegal() << std::endl;


	//lol.outputLegalMoves();
	board b;
	b.print();

	b.movePiece(lol);
	b.print();
	
	//lol.visualizeLegalMoves();

	b.generateMoves();
	b.printCoordinateMap();

	std::cin.get();
    return 0;
}
