#include "tests.h"
#include "bitchess.h"

void testmove() {
	{
		board::move m(piece::w_pawn, "b2", "b4");
		assert(m.getPiece() == piece::w_pawn);
		assert(m.getFrom()  == board::coordinate("b2"));
		assert(m.getTo()    == board::coordinate("b4"));
	}
}