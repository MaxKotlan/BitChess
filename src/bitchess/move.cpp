//
// Created by Konstantin Gredeskoul on 5/14/17.
//

#include "move.h"

#include <algorithm>


std::vector<board::move> board::move::_legalmoves;
std::vector<board::move> board::move::_legalmoves_sorted;


board::move::move(piece p, coordinate from, coordinate to) : _data(0) {
	_data += uint16_t(p);
	_data += (uint16_t(from) << 4);
	_data += (uint16_t(to) << 10);
};


board::coordinate board::move::getFrom() const{ 
	return ((_data >> 4) % 64); 
};

board::coordinate board::move::getTo() const{ 
	return ((_data >> 10) % 64); 
};

std::ostream& operator<< (std::ostream& stream, const board::move& out) {
	stream << std::hex << "0x" << out._data << " [" << piece::getHumanReadable(out.getPiece()).c_str() << ", " << out.getFrom().getDisplayCoordinates().c_str() << ", " << out.getTo().getDisplayCoordinates().c_str() << "]";
	return stream;
}

bool board::move::isLegal() {
	//auto result = std::find(_legalmoves.begin(), _legalmoves.end(), *this);
	//return (result != _legalmoves.end());
	return std::binary_search(_legalmoves_sorted.begin(), _legalmoves_sorted.end(), *this);
}


void board::move::generateValidMoves() {
	for (uint8_t p = piece::w_pawn; p <= piece::b_king; p++) {
		for (uint8_t c = 0; c < 64; c++) {
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
	_legalmoves_sorted = _legalmoves;
	std::sort(_legalmoves_sorted.begin(), _legalmoves_sorted.end());
}

void board::move::outputLegalMoves() {
	for (auto it = _legalmoves.begin(); it != _legalmoves.end(); it++)
		std::cout << *it << std::endl;
}

uint16_t board::move::getTotalLegalMoves() {
	return _legalmoves.size();
}

void board::move::visualizeLegalMoves() {
	coordinate prev;
	board b;
	b.clear();
	for (auto it = _legalmoves.begin(); it != _legalmoves.end(); it++) {
		if (prev != it->getFrom()) {
			b.print();
			std::cout << "------------------------------------------------" << std::endl;
			b.clear();
			b.addPiece(0xF, it->getFrom()); /*Add undefined piece to signify current piece location*/
		}
		b.addPiece(it->getPiece(), it->getTo());
		prev = it->getFrom();
	}
	std::cout << "TOTAL: " << _legalmoves.size() << std::endl;
}


void board::move::north(piece p, coordinate c, uint8_t rangeLimit) {
	coordinatePattern(p, c, 8, 1, rangeLimit);
}

void board::move::south(piece p, coordinate c, uint8_t rangeLimit) {
	coordinatePattern(p, c, -8, -1, rangeLimit);
}

void board::move::east(piece p, coordinate c, uint8_t rangeLimit) {
	coordinatePattern(p, c, -1, 0, rangeLimit);
}

void board::move::west(piece p, coordinate c, uint8_t rangeLimit) {
	coordinatePattern(p, c,  1, 0, rangeLimit);
}

void board::move::northdiagnals(piece p, coordinate c, uint8_t rangeLimit) {
	coordinatePattern(p, c, 9, 1, rangeLimit);
	coordinatePattern(p, c, 7, 1, rangeLimit);
}

void board::move::southdiagnals(piece p, coordinate c, uint8_t rangeLimit) {
	coordinatePattern(p, c, -9, -1, rangeLimit);
	coordinatePattern(p, c, -7, -1, rangeLimit);
}

void board::move::coordinatePattern(piece p, coordinate c, int corddelta, int rowdelta, uint8_t rangeLimit) {
	coordinate od = c, nw = c + corddelta;
	int count = 0;
	while ((od.getRow() + rowdelta) == nw.getRow() && nw.isValid() && count < rangeLimit) {
		_legalmoves.push_back(move(p, c, nw));
		od = nw;
		nw = nw + corddelta;
		count++;
	}
}


void board::move::gen_w_pawn_moves(coordinate c) {

	if (c.getRow() != 0) { /*white pawns pawns cannot be in the first row in a standard chess game */

		if (c.getRow() == 1) /*if pawn is in the first row, it has a range of two*/
			north(piece::w_pawn, c, 2);
		else
			north(piece::w_pawn, c, 1);

		northdiagnals(piece::w_pawn, c, 1);
	}
}

void board::move::gen_b_pawn_moves(coordinate c) {

	if (c.getRow() != 7) { /*black pawns pawns cannot be in the last row in a standard chess game */

		if (c.getRow() == 6) /*if pawn is in the first row, it has a range of two*/
			south(piece::b_pawn, c, 2);
		else
			south(piece::b_pawn, c, 1);

		southdiagnals(piece::b_pawn, c, 1);
	}
}

void board::move::gen_knig_moves(piece p, coordinate c) {
	coordinatePattern(p, c, 15, 2, 1);
	coordinatePattern(p, c, 17, 2, 1);

	coordinatePattern(p, c, 6, 1, 1);
	coordinatePattern(p, c, 10, 1, 1);

	coordinatePattern(p, c,  -6, -1, 1);
	coordinatePattern(p, c, -10, -1, 1);

	coordinatePattern(p, c, -15, -2, 1);
	coordinatePattern(p, c, -17, -2, 1);

}


void board::move::gen_bish_moves(piece p, coordinate c) {
	northdiagnals(p, c, 9);
	southdiagnals(p, c, 9);
}

void board::move::gen_rook_moves(piece p, coordinate c) {
	north(p, c, 9);
	south(p, c, 9);
	east(p, c, 9);
	west(p, c, 9);
}

void board::move::gen_quee_moves(piece p, coordinate c) {
	north(p, c, 9);
	south(p, c, 9);
	east(p, c, 9);
	west(p, c, 9);
	northdiagnals(p, c, 9);
	southdiagnals(p, c, 9);
}

void board::move::gen_king_moves(piece p, coordinate c) {
	north(p, c, 1);
	south(p, c, 1);
	east(p, c, 1);
	west(p, c, 1);
	northdiagnals(p, c, 1);
	southdiagnals(p, c, 1);
}

bool board::move::operator == (board::move rhs) {
	return (_data == rhs._data);
}

bool board::move::operator != (board::move rhs) {
	return (_data != rhs._data);
}

/*
bool board::move::operator < (board::move rhs) {
	return (_data < rhs._data);
}

bool board::move::operator > (board::move rhs) {
	return (_data > rhs._data);
}

bool board::move::operator <= (board::move rhs) {
	return (_data <= rhs._data);
}

bool board::move::operator >= (board::move rhs) {
	return (_data >= rhs._data);
}*/

bool operator <(board::move left, board::move right)
{
	return left.getRaw() < right.getRaw();
}

bool operator >(board::move left, board::move right)
{
	return left.getRaw() > right.getRaw();
}