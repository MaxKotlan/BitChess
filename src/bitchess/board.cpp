//
// Created by Konstantin Gredeskoul on 5/14/17.
//

#include <time.h>
#include <thread>
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

void board::movePiece(board::move m) {
	addPiece(m.getPiece(), m.getTo());
	removePiece(m.getFrom());
}

void board::generateMoves(int co) {
	std::vector<board::move> kek;

	board::move m(piece::w_pawn, "a2", "a3");
	//returnLegal(kek, piece::w_bish, "d4");
	//for (auto i = 0; i < 64; i++) {
	//	m.returnLegal(kek, getPiece(i), i);
	//}
	//int numpei = 0;
	//for (int i = 0; i < 63; i++)
	//	numpei += uint8_t(getPiece(i));
	//board *next = new board(*this);

	//for (auto mv = kek.begin(); mv != kek.end(); mv++) {
		//std::cout << *mv << " " << (mv->isDiagnal() ? "true " : "false") <<  " " << std::dec<< (int)mv->distance() << std::endl;
	//if (kek.size() > 0 &&  numpei > 0xC) {
	//	move rm = kek[rand() % kek.size()];
		//while (getPiece(rm.getTo()) != piece::empty) {
		//	rm = kek[rand() % kek.size()];
		//}
	//	if (uint8_t(getPiece(rm.getTo())) != piece::empty) {
	//		if (uint8_t(getPiece(rm.getTo())) >= 7 && rm.getFrom() < 7 ||
	//			uint8_t(getPiece(rm.getTo())) < 7 && rm.getFrom() >= 7
		//		) {
		//		next->removePiece(rm.getTo());
		//	}
	//	}
	//	else {
	//		kek.empty();
	//		next->movePiece(rm);
	//	}
		//std::cout << "---------------------------------------" << std::endl;
		//print();
		//next->generateMoves(co+1);
	//	delete next;
	//}
	//}
	std::cout << co << ", " << kek.size() << std::endl;

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
	//_validmoves.clear();
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

void board::printCoordinateMap() {
	for (board::row r = 7; r >= 0; r--) {
		for (board::col c = 0; c < 8; c++) {
			std::cout << std::dec << "[";
			if (r * 8 + c < 10)
				std::cout << " ";
			std::cout << (r) * 8 + c << "]";
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

bool board::freeSpace(coordinate c) {
	return getPiece(c) == piece::code::empty; 
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