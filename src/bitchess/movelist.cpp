#include "movelist.h"

#include <algorithm>


movenode::movenode(board::move m){
	move_header = m.getHeader();
	range.push_back(m);
};

movelist::movelist() {

	for (uint8_t c = 0; c < 64; c++) {
		for (uint8_t p = piece::w_pawn; p <= piece::b_king; p++) {
			switch (p)
			{
			case piece::w_pawn: gen_w_pawn_moves(c); break;
			case piece::b_pawn: gen_b_pawn_moves(c); break;

			case piece::w_knig: case piece::b_knig: gen_knig_moves(p, c); break;
			case piece::w_bish: case piece::b_bish: gen_bish_moves(p, c); break;
			case piece::w_rook: case piece::b_rook: gen_rook_moves(p, c); break;
			case piece::w_quee: case piece::b_quee: gen_quee_moves(p, c); break;
			case piece::w_king: case piece::b_king: gen_king_moves(p, c); break;

			}
		}
	}
	std::sort(_legalmoves.begin(), _legalmoves.end()); /*can probably remove this later once fully develop piece class, and insert in proper order*/
}

void movelist::getLegalMovesIndex(piece p, board::coordinate from, uint8_t d) {
	uint16_t header = 0; header += d + (uint16_t(p) << 3) + (uint16_t(from) << 7);
	std::cout << std::hex << header << std::endl;
	auto startin = std::lower_bound(_legalmoves.begin(), _legalmoves.end(), header);
	for (auto it = startin->range.begin(); it != startin->range.end(); it++){
		std::cout << it->getHeader() << *it << std::endl;
	}
};

int movelist::listSize() {
	int size = 0;
	for (auto it = _legalmoves.begin(); it != _legalmoves.end(); it++) {
		for (auto kt = it->range.begin(); kt != it->range.end(); kt++) {
			size++;
		}
	}
	return size;
}

void movelist::print() {
	for (auto it = _legalmoves.begin(); it != _legalmoves.end(); it++) {
		//std::cout << "HEADER: " << it->move_header << " |: ";
		for (auto kt = it->range.begin(); kt != it->range.end(); kt++) {
			std::cout << "HED: " <<  it->move_header << " | " << *kt << " " << getDirectionCode(kt->getDirection()).c_str() << std::endl; //" |, ";
		}
		//std::cout << std::endl;
	}
}

void movelist::north(piece p, board::coordinate c, uint8_t rangeLimit) {
	coordinatePattern(p, c, 8, 1, rangeLimit);
}

void movelist::south(piece p, board::coordinate c, uint8_t rangeLimit) {
	coordinatePattern(p, c, -8, -1, rangeLimit);
}

void movelist::east(piece p, board::coordinate c, uint8_t rangeLimit) {
	coordinatePattern(p, c, -1, 0, rangeLimit);
}

void movelist::west(piece p, board::coordinate c, uint8_t rangeLimit) {
	coordinatePattern(p, c, 1, 0, rangeLimit);
}

void movelist::northdiagnals(piece p, board::coordinate c, uint8_t rangeLimit) {
	coordinatePattern(p, c, 9, 1, rangeLimit);
	coordinatePattern(p, c, 7, 1, rangeLimit);
}

void movelist::southdiagnals(piece p, board::coordinate c, uint8_t rangeLimit) {
	coordinatePattern(p, c, -9, -1, rangeLimit);
	coordinatePattern(p, c, -7, -1, rangeLimit);
}

void movelist::coordinatePattern(piece p, board::coordinate c, int corddelta, int rowdelta, uint8_t rangeLimit) {
	board::coordinate od = c, nw = c + corddelta;
	int count = 0;
	while ((od.getRow() + rowdelta) == nw.getRow() && nw.isValid() && count < rangeLimit) {
		board::move nm = board::move(p, c, nw);
		if (_legalmoves.size() > 0) {
			if (_legalmoves.back().move_header != nm.getHeader()) {
				_legalmoves.push_back(nm);
			}
			else {
				_legalmoves.back().range.push_back(nm);
			}
		}
		else {
			_legalmoves.push_back(nm);
		}
		od = nw;
		nw = nw + corddelta;
		count++;
	}

}

void movelist::gen_w_pawn_moves(board::coordinate c) {

	if (c.getRow() != 0) { /*white pawns pawns cannot be in the first row in a standard chess game */

		if (c.getRow() == 1) /*if pawn is in the first row, it has a range of two*/
			north(piece::w_pawn, c, 2);
		else
			north(piece::w_pawn, c, 1);

		northdiagnals(piece::w_pawn, c, 1);
	}
}

void movelist::gen_b_pawn_moves(board::coordinate c) {

	if (c.getRow() != 7) { /*black pawns pawns cannot be in the last row in a standard chess game */

		if (c.getRow() == 6) /*if pawn is in the first row, it has a range of two*/
			south(piece::b_pawn, c, 2);
		else
			south(piece::b_pawn, c, 1);

		southdiagnals(piece::b_pawn, c, 1);
	}
}

void movelist::gen_knig_moves(piece p, board::coordinate c) {
	coordinatePattern(p, c, 15, 2, 1);
	coordinatePattern(p, c, 17, 2, 1);

	coordinatePattern(p, c, 6, 1, 1);
	coordinatePattern(p, c, 10, 1, 1);

	coordinatePattern(p, c, -6, -1, 1);
	coordinatePattern(p, c, -10, -1, 1);

	coordinatePattern(p, c, -15, -2, 1);
	coordinatePattern(p, c, -17, -2, 1);

}


void movelist::gen_bish_moves(piece p, board::coordinate c) {
	northdiagnals(p, c, 9);
	southdiagnals(p, c, 9);
}

void movelist::gen_rook_moves(piece p, board::coordinate c) {
	north(p, c, 9);
	south(p, c, 9);
	east(p, c, 9);
	west(p, c, 9);
}

void movelist::gen_quee_moves(piece p, board::coordinate c) {
	north(p, c, 9);
	south(p, c, 9);
	east(p, c, 9);
	west(p, c, 9);
	northdiagnals(p, c, 9);
	southdiagnals(p, c, 9);
}

void movelist::gen_king_moves(piece p, board::coordinate c) {
	north(p, c, 1);
	south(p, c, 1);
	east(p, c, 1);
	west(p, c, 1);
	northdiagnals(p, c, 1);
	southdiagnals(p, c, 1);

	/*Castling*/
	if (c == "e1" && p == piece::w_king) {
		coordinatePattern(p, c, +2, 0, 1);
		coordinatePattern(p, c, -2, 0, 1);
	}
	if (c == "e8" && p == piece::b_king) {
		coordinatePattern(p, c, +2, 0, 1);
		coordinatePattern(p, c, -2, 0, 1);
	}



}

/*
bool board::move::operator == (board::move rhs) {
	return (_data == rhs._data);
}

bool board::move::operator != (board::move rhs) {
	return (_data != rhs._data);
}

*/

bool operator <(movenode left, uint16_t right)
{
	return left.move_header < right;
}

bool operator >(movenode left, uint16_t right)
{
	return left.move_header > right;
}



bool operator <(movenode left, movenode right)
{
	return left.move_header < right.move_header;
}

bool operator >(movenode left, movenode right)
{
	return left.move_header > right.move_header;
}