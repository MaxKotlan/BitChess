#pragma once

#include "bitchess.h"

struct movenode {
	typedef uint16_t header;
	/*Combination of From Coordinate and Piece*/
	header move_header;
	/*Vector of coordinates in from range*/
	std::vector<board::move> range;

	movenode(board::move m);

	friend bool operator <(movenode m, uint16_t g);
	friend bool operator >(movenode m, uint16_t g);
	friend bool operator <(movenode m, movenode g);
	friend bool operator >(movenode m, movenode g);
};

class movelist {
	public:
		static movelist& getInstance()
		{
			static movelist instance; // Guaranteed to be destroyed.
								  // Instantiated on first use.
			return instance;
		}

		void print();
		int listSize();
		std::vector<movenode>::iterator getLegalMovesIndex(piece p, board::coordinate from, uint8_t d);
		std::vector<movenode>::iterator notfound;
	protected:
	/*Add legal moves to list for each type of piece*/
	void gen_w_pawn_moves(board::coordinate c);
	void gen_b_pawn_moves(board::coordinate c);
	void gen_knig_moves(piece p, board::coordinate c);
	void gen_bish_moves(piece p, board::coordinate c);
	void gen_rook_moves(piece p, board::coordinate c);
	void gen_quee_moves(piece p, board::coordinate c);
	void gen_king_moves(piece p, board::coordinate c);

	/*Generic function used to generate patterns shared by pieces (like diagnal or straight lines)*/
	void coordinatePattern(piece p, board::coordinate c, int corddelta, int rowdelta, uint8_t rangeLimit);

	/*more specific directional functions*/
	void north(piece p, board::coordinate c, uint8_t rangeLimit);
	void south(piece p, board::coordinate c, uint8_t rangeLimit);
	void  east(piece p, board::coordinate c, uint8_t rangeLimit);
	void  west(piece p, board::coordinate c, uint8_t rangeLimit);

	void northdiagnals(piece p, board::coordinate c, uint8_t rangeLimit);
	void southdiagnals(piece p, board::coordinate c, uint8_t rangeLimit);

	private:
		movelist();
		std::vector<movenode> _legalmoves;
};