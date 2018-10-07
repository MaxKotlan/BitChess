#include "bitchess.h"
#include <vector>
#include <stack>
#include <unordered_map> 
#include <unordered_set>
#include <iostream>
#include <fstream>

int main(int argc, const char *argv[]) {
	
	ofstream myfile;
	myfile.open("example.csv");

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

	std::unordered_set<uint16_t> set;

	for (auto n = b._validmoves.begin(); n != b._validmoves.end(); n++) {
		set.insert(n->getRaw());
		myfile << std::dec << n->getRaw() << "," << piece::getHumanReadable(n->getPiece()).c_str() << "," << (int)n->getFrom() << "," << (int)n->getTo() << ",\n";
	}

	if (set.find(board::move(piece::w_pawn, "c3", "c5").getRaw()) == set.end()) {
		std::cout << "Move is Invalid" << std::endl;
	}
	else {
		std::cout << "Move is Valid" << std::endl;
	}

	myfile.close();

	board::move moer(piece::w_bish, "c1", "c2"); moer.generateValidMoves();

	moer.outputLegalMoves();
	std::cout << "TOTAL LEGAL MOVES: " << moer.getTotalLegalMoves() << std::endl;

	std::cout << "Total Legal Moves: " << b.validMoveSize() << std::endl;



	std::cin.get();
    return 0;
}
