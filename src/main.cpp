#include "bitchess.h"
#include <vector>
#include <stack>
#include <unordered_map> 
#include <unordered_set>
#include <iostream>
#include <fstream>
#include <time.h>

int main(int argc, const char *argv[]) {
	
	board::move k(piece::w_king, "d4", "d5");
	k.generateValidMoves();

	srand(time(nullptr));

	std::cout << "TOTAL LEGAL MOVES: " << k.getTotalLegalMoves() << std::endl;
	double illegal = 0, legal = 0;
	for (auto t = 0; t < 14; t++) {
		for (auto i = 0; i < 10000; i++) {
			k = board::move(rand() % 13 + 1, rand() % 64, rand() % 64);
			bool legality = k.isLegal();
			//std::cout << k << "is legal? " << ((legality) ? "true" : "false") << std::endl;
			if (legality) legal++; else illegal++;
		}
		std::cout << "TRIAL " << t <<  ": ILLEGAL: " << illegal << ", " << illegal / 10000 << " | LEGAL" << legal << ", " << legal / 10000 << std::endl;
		illegal = 0; legal = 0;
	}
	std::cin.get();
    return 0;
}
