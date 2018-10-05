//
// Created by Konstantin Gredeskoul on 5/14/17.
//

#include <time.h>
#include "board.h"

board::board() {
	_row[7] = 0xA89CB98A;
	_row[6] = 0x77777777;
	_row[5] = 0x00000000;
	_row[4] = 0x00000000;
	_row[3] = 0x00000000;
	_row[2] = 0x00000000;
	_row[1] = 0x11111111;
	_row[0] = 0x42365324;
}

void board::addPiece(piece p, coordinate c){
	_row[c.getRow()] += uint32_t(p) << c.getCol() * piece::code_bits;
}

void board::movePiece(coordinate from, coordinate to) {
	addPiece(getPiece(from), to);
	removePiece(from);
}

void board::removePiece(coordinate c) {
	_row[c.getRow()] -= uint32_t(getPiece(c)) << c.getCol() * piece::code_bits;
}

void board::promotePiece(piece promotion, coordinate c) {
	removePiece(c);
	addPiece(promotion, c);
}

void board::clear() {
	for (board::row r = 0; r < 8; r++)
		_row[r] = 0;
}

void board::random() {
	srand(time(nullptr));
	for (board::row r = 0; r < 8; r++)
		for (board::col c = 0; c < 8; c++)
			_row[r] +=  rand() % 0xC << c ;
}

void board::printRaw() {
	for (board::row r = 8; r >= 0; r--)
		std::cout << std::hex << _row[r] << std::endl;
}

void board::printUTF() {
	for (board::row r = 7; r >= 0; r--) {
		for (board::col c = 0; c < 8; c++) {
			std::wcout << "[" <<
				piece::getUTF8(
					static_cast<piece::code>(
					(_row[r] >> c * piece::code_bits) % 16 /*Gets Piece Code from row integer*/
						)
				)
				<< "]";
		}
		std::cout << std::endl;
	}
}

void board::print() {
	for (board::row r = 7; r >= 0; r--) {
		for (board::col c = 0; c < 8; c++) {
			std::cout << "[" <<
				piece::getHumanReadable(
					static_cast<piece::code>(
						(_row[r] >> c * piece::code_bits) % 16 /*Gets Piece Code from row integer*/
					)
				).c_str()
				<< "]";
		}
		std::cout << std::endl;
	}
}


piece board::getPiece(coordinate c) {
	return ( _row[c.getRow()] >> c.getCol() * piece::code_bits) % 16 ;
}

bool board::operator==(const board& rhs) {
	for (board::row r = 0; r < 8; r++)
		if (_row[r] != rhs._row[r]) return false;
	return true;
}

bool board::operator!=(const board& rhs) {
	return !(*this == rhs);
}

void board::printValidMoves() {
	for (auto it = _validmoves.begin(); it != _validmoves.end(); it++)
		std::cout << *it << std::endl;
}

void board::generateValidMoves() {
	for (auto c = 0; c < 64; c++) {
		piece p = getPiece(c);
		switch (piece::code(p))
		{
			case piece::code::w_pawn:
				if (coordinate(c).getRow() == 1)
					_validmoves.push_back(move(piece::code::w_pawn, c, c + 16));
				_validmoves.push_back(move(piece::code::w_pawn, c, c+8));
			break;
			case piece::code::w_bish:

				break;

		default:
			break;
		}
	}
}