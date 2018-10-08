#include "tests.h"
#include "bitchess.h"
#include <time.h>
#include <thread>

void sample(int contin) {
	double sm = 64 * 64 * 16;
	double illegal = 0, legal = 0;
	board::move k(piece::w_king, "d4", "d5");
	for (auto i = 0; i < sm; i++) {
		k = board::move(rand() % 13 + 1, rand() % 64, rand() % 64);
		//k.randomLegal();
		bool legality = k.isLegal();
		//		std::cout << k << "is legal? " << ((legality) ? "true" : "false") << "\n";
		if (legality) legal++; else illegal++;
	}
	std::cout << "LEGAL: " << legal << " ILLEGAL: " << illegal << "\n";
	if (contin <= 1000)
		sample(contin+1);
}

void testmove() {
	{
		board::move m(piece::w_pawn, "b2", "b4");
		assert(m.getPiece() == piece::w_pawn);
		assert(m.getFrom()  == board::coordinate("b2"));
		assert(m.getTo()    == board::coordinate("b4"));
	}
	{
		board::move k(piece::w_king, "d4", "d5");
		k.generateValidMoves();

		srand(time(nullptr));

		std::cout << "TOTAL LEGAL MOVES: " << k.getTotalLegalMoves() << std::endl;
		
		std::thread first  (sample,0);
		std::thread second (sample,0);
		std::thread third  (sample,0);
		std::thread fourth (sample,0);
		first.join();
		second.join();
		third.join();
		fourth.join();
		std::cin.get();
		std::cout << "TOTAL: " << 4 * 64 * 64 * 16 << std::endl;
	}
}