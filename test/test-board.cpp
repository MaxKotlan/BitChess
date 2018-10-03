#include "tests.h"
#include "bitchess.h"

#include <cassert>

void testboard() {
	std::cout << "------Testing Board Size ------" << std::endl;
	{
		board b;
		assert(sizeof(b) == sizeof( uint32_t) *8);
		assert(sizeof(b) == 32);
	}
	std::cout << "------Testing Get Piece Function ------" << std::endl;
	{
		board b;		
		assert(b.getPiece("a1") == piece::code::w_rook);
		assert(b.getPiece("b1") == piece::code::w_knig);
		assert(b.getPiece("c1") == piece::code::w_bish);
		assert(b.getPiece("d1") == piece::code::w_quee);
		assert(b.getPiece("e1") == piece::code::w_king);
		assert(b.getPiece("d2") == piece::code::w_pawn);

		assert(b.getPiece("d3") == piece::code::empty);

		assert(b.getPiece("a8") == piece::code::b_rook);
		assert(b.getPiece("b8") == piece::code::b_knig);
		assert(b.getPiece("c8") == piece::code::b_bish);
		assert(b.getPiece("d8") == piece::code::b_quee);
		assert(b.getPiece("e8") == piece::code::b_king);
		assert(b.getPiece("d7") == piece::code::b_pawn);

	}

}