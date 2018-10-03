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
	for (board::row r = 8; r >= 0; r--) {
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
	for (board::row r = 8; r >= 0; r--) {
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