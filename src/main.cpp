﻿#include "bitchess.h"
#include <vector>
#include <stack>
#include <unordered_map> 
#include <unordered_set>
#include <iostream>
#include <fstream>
#include <time.h>

int main(int argc, const char *argv[]) {
	
	board::move lol(piece::w_pawn, "d2", "d4");

	//lol.outputLegalMoves();
	board b;
	b.print();

	b.movePiece(lol);
	b.print();
	
	//lol.visualizeLegalMoves();

	srand(time(nullptr));
	
	/*
	movelist k = movelist::getInstance();
	k.print();
	for (int i = 0; i < 8; i++) {
		auto start = k.getLegalMovesIndex(piece::w_quee, "d4", i)->range;
		for (auto it = start.begin(); it != start.end(); it++) {
			std::cout << *it << std::endl;
		}

	} */

	b.generateMoves(0);


	b.printCoordinateMap();

	std::cin.get();
    return 0;
}
