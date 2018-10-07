#include "bitchess.h"
#include <vector>
#include <stack>
#include <unordered_map> 
#include <unordered_set>
#include <iostream>
#include <fstream>

int main(int argc, const char *argv[]) {
	
	board::move k(piece::w_king, "d4", "c4");
	k.generateValidMoves();
	std::cout << "TOTAL LEGAL MOVES: " << k.getTotalLegalMoves() << std::endl;


	std::cin.get();
    return 0;
}
