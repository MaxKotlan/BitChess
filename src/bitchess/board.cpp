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

#include <io.h>
#include <fcntl.h>

void board::print() {
	_setmode(_fileno(stdout), _O_WTEXT);
	for (board::row r = 0; r < 8; r++) {
		for (board::col c = 0; c < 8; c++) {
			std::wcout << "[" <<
				piece::getHumanReadable(
					static_cast<piece::code>(
						(_row[r] >> c * piece::code_bits) % 16 /*Gets Piece Code from row integer*/
					)
				).c_str()
				<< "]";
		}
		std::wcout << std::endl;
	}
}


piece board::getPiece(coordinate c) {
	return static_cast<piece::code>(
		_row[c.getRow()] >> c.getCol() * piece::code_bits );
}