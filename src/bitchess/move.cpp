//
// Created by Konstantin Gredeskoul on 5/14/17.
//

#include "move.h"

#include <algorithm>
#include <fstream>

std::vector<board::move> board::move::_legalmoves;
std::vector<board::move> board::move::_legalmoves_sorted;


board::move::move(piece p, coordinate from, coordinate to) : _data(0) {
	_data += uint16_t(p) << 6;
	_data += (uint16_t(from) << 10);
	_data += (uint16_t(to));
};


board::coordinate board::move::getFrom() const{ 
	return ((_data >> 10) % 64); 
};

board::coordinate board::move::getTo() const{ 
	return ((_data) % 64); 
};

std::ostream& operator<< (std::ostream& stream, const board::move& out) {
	stream << std::hex << "0x" << out._data << " [" << piece::getHumanReadable(out.getPiece()).c_str() << ", " << out.getFrom().getDisplayCoordinates().c_str() << ", " << out.getTo().getDisplayCoordinates().c_str() << "]";
	return stream;
}

void board::move::randomLegal() {
	_data = _legalmoves_sorted[rand() % _legalmoves_sorted.size()]._data;
}

bool board::move::isLegal() {
	//auto result = std::find(_legalmoves.begin(), _legalmoves.end(), *this);
	//return (result != _legalmoves.end());
	return std::binary_search(_legalmoves_sorted.begin(), _legalmoves_sorted.end(), *this); /*Use binary search to find if move is legal*/
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
	auto ns = _legalmoves.begin();
	
	for (auto it = _legalmoves_sorted.begin(); it != _legalmoves_sorted.end(); it++) {
		std::cout << *it << " | " << *ns << std::endl;
		ns++;
	}
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

/*Needs improvement*/
bool board::move::isDiagnal() {
	return (distance()%7 == 0 || distance()%9 == 0);
}


uint8_t board::move::distance() {
	coordinate from = getFrom();
	coordinate to = getTo();
	if (getFrom() > getTo()) return getFrom() - getTo();
	else return getTo() - getFrom();
}

std::vector<board::move>::iterator ub(std::vector<board::move>::iterator first, std::vector<board::move>::iterator last, board::move val)
{
	std::vector<board::move>::iterator it;
	iterator_traits<std::vector<board::move>::iterator>::difference_type count, step;
	count = std::distance(first, last);
	while (count>0)
	{
		it = first; step = count / 2; std::advance(it, step);
		if (!((val.getRaw() >> 6)<(it->getRaw() >> 6)))                // or: if (!comp(val,*it)), for version (2)
		{
			first = ++it; count -= step + 1;
		}
		else count = step;
	}
	return first;
}

std::vector<board::move>::iterator lb(std::vector<board::move>::iterator first, std::vector<board::move>::iterator last, board::move val)
{
	std::vector<board::move>::iterator it;
	iterator_traits<std::vector<board::move>::iterator>::difference_type count, step;
	count = distance(first, last);
	while (count>0)
	{
		it = first; step = count / 2; advance(it, step);
		if ((it->getRaw() >> 6) < (val.getRaw() >> 6)) {                 // or: if (comp(*it,val)), for version (2)
			first = ++it;
			count -= step + 1;
		}
		else count = step;
	}
	return first;
}

void board::move::returnLegal(std::vector<board::move>& mov, piece p, board::coordinate c){
		move fer(p, c, "a1");
		auto beg = lb(_legalmoves_sorted.begin(), _legalmoves_sorted.end(), fer);
		auto end = ub(beg, _legalmoves_sorted.end(), fer);
		for (auto it = beg; it != end; it++) {
			mov.push_back(*it);
		}
	//	if (it->getFrom() == c && uint8_t(it->getPiece()) == uint8_t(p))
	//		mov.push_back(board::move(p, c, it->getTo()));
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

bool board::move::operator == (board::move rhs) {
	return (_data == rhs._data);
}

bool board::move::operator != (board::move rhs) {
	return (_data != rhs._data);
}


bool operator <(board::move left, board::move right)
{
	return left.getRaw() < right.getRaw();
}

bool operator >(board::move left, board::move right)
{
	return left.getRaw() > right.getRaw();
}