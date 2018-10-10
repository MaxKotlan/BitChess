#pragma once

#include <iostream>
#include <vector>
#include "bitchess.h"


class board::move {
public:
	move(piece p, coordinate from, coordinate to);

	piece getPiece() const { return piece((_data >> 6)% 16); };
	coordinate getFrom() const;
	coordinate getTo() const;
	uint16_t getRaw() {return _data;};

	void randomLegal();

	bool isLegal();

	friend std::ostream& operator<< (std::ostream& stream, const board::move& move);

	uint16_t getTotalLegalMoves();

	void generateValidMoves();
	void outputLegalMoves();
	void visualizeLegalMoves();

	bool operator == (move rhs);
	bool operator != (move rhs);

	friend bool operator <(board::move m, board::move g);
	friend bool operator >(board::move m, board::move g);

	uint8_t distance();

	bool isDiagnal();

	void returnLegal(std::vector<move>& mov, piece p, coordinate c);

	protected:

		/*Add legal moves to list for each type of piece*/
		void gen_w_pawn_moves(coordinate c);
		void gen_b_pawn_moves(coordinate c);
		void gen_knig_moves(piece p, coordinate c);
		void gen_bish_moves(piece p, coordinate c);
		void gen_rook_moves(piece p, coordinate c);
		void gen_quee_moves(piece p, coordinate c);
		void gen_king_moves(piece p, coordinate c);

		/*Generic function used to generate patterns shared by pieces (like diagnal or straight lines)*/
		void coordinatePattern(piece p, coordinate c, int corddelta, int rowdelta, uint8_t rangeLimit);

		/*more specific directional functions*/
		void north(piece p, coordinate c, uint8_t rangeLimit); 
		void south(piece p, coordinate c, uint8_t rangeLimit);
		void  east(piece p, coordinate c, uint8_t rangeLimit);
		void  west(piece p, coordinate c, uint8_t rangeLimit);

		void northdiagnals(piece p, coordinate c, uint8_t rangeLimit);
		void southdiagnals(piece p, coordinate c, uint8_t rangeLimit);


	private:
		uint16_t _data;
		static std::vector<move> _legalmoves;
		static std::vector<move> _legalmoves_sorted;
};

