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

void board::printValidMoves() {
	for (auto it = _validmoves.begin(); it != _validmoves.end(); it++)
		std::cout << *it << std::endl;
}

void board::printMoveMap() {
	board mm;
	mm.clear();
	for (auto it = _validmoves.begin(); it != _validmoves.end(); it++)
		mm.addPiece(it->getPiece(), it->getTo());
	mm.print();
}

int board::validMoveSize() {
	return _validmoves.size();
}

void board::generateValidMoves() {
	for (auto c = 0; c < 64; c++) {
		switch (piece::code(getPiece(c)))
		{
			case piece::code::w_pawn: generateWhitePawnMoves(c); break;
			case piece::code::w_knig: generateKnightMoves(c);    break;
			case piece::code::w_bish: generateBishopMoves(c);    break;
			case piece::code::w_rook: generateRookMoves(c);      break;
			case piece::code::w_quee: generateQueenMoves(c);     break;
			case piece::code::w_king: generateKingMoves(c);      break;
		}
	}
}

void board::generateWhitePawnMoves(coordinate c) {

	if (c >= 8) {

		coordinate od = c, nw = c + 16;
		if (coordinate(c).getRow() == 1 && od.getRow() + 2 == nw.getRow() && nw.isValid())
			_validmoves.push_back(move(piece::code::w_pawn, c, nw));

		od = c, nw = c + 8;
		if (od.getRow() + 1 == nw.getRow() && nw.isValid())
			_validmoves.push_back(move(piece::code::w_pawn, c, nw));

		od = c, nw = c + 9;
		if (od.getRow() + 1 == nw.getRow() && nw.isValid())
			_validmoves.push_back(move(piece::code::w_pawn, c, nw));

		od = c, nw = c + 7;
		if (od.getRow() + 1 == nw.getRow() && nw.isValid())
			_validmoves.push_back(move(piece::code::w_pawn, c, nw));
	}
}

void board::generateKnightMoves(coordinate c) {
	coordinate od = c, nw = c + 15;
	if (od.getRow() + 2 == nw.getRow() && nw.isValid())
		_validmoves.push_back(move(piece::code::w_king, c, nw));
	od = c, nw = c + 17;
	if (od.getRow() + 2 == nw.getRow() && nw.isValid())
		_validmoves.push_back(move(piece::code::w_king, c, nw));
	od = c, nw = c + 6;
	if (od.getRow() + 1 == nw.getRow() && nw.isValid())
		_validmoves.push_back(move(piece::code::w_king, c, nw));
	od = c, nw = c + 10;
	if (od.getRow() + 1 == nw.getRow() && nw.isValid())
		_validmoves.push_back(move(piece::code::w_king, c, nw));

	od = c, nw = c - 15;
	if (od.getRow() - 2 == nw.getRow() && nw.isValid())
		_validmoves.push_back(move(piece::code::w_king, c, nw));
	od = c, nw = c - 17;
	if (od.getRow() - 2 == nw.getRow() && nw.isValid())
		_validmoves.push_back(move(piece::code::w_king, c, nw));
	od = c, nw = c - 6;
	if (od.getRow() - 1 == nw.getRow() && nw.isValid())
		_validmoves.push_back(move(piece::code::w_king, c, nw));
	od = c, nw = c - 10;
	if (od.getRow() - 1 == nw.getRow() && nw.isValid())
		_validmoves.push_back(move(piece::code::w_king, c, nw));

}

void board::generateBishopMoves(coordinate c) {
	coordinate od = c, nw = c+9;
	while (od.getRow()+1 == nw.getRow() && nw.isValid()) {
		_validmoves.push_back(move(piece::code::w_bish, c, nw));
		od = nw;
		nw = od + 9;
	}
	od = c, nw = c + 7;
	while (od.getRow() + 1 == nw.getRow() && nw.isValid()) {
		_validmoves.push_back(move(piece::code::w_bish, c, nw));
		od = nw;
		nw = od + 7;
	}
	od = c, nw = c - 7;
	while (od.getRow() - 1 == nw.getRow() && nw.isValid()) {
		_validmoves.push_back(move(piece::code::w_bish, c, nw));
		od = nw;
		nw = od - 7;
	}
	od = c, nw = c - 9;
	while (od.getRow() - 1 == nw.getRow() && nw.isValid()) {
		_validmoves.push_back(move(piece::code::w_bish, c, nw));
		od = nw;
		nw = od - 9;
	}
}

void board::generateRookMoves(coordinate c) {
	coordinate od = c, nw = c + 8;
	while (od.getRow() + 1 == nw.getRow() && nw.isValid()) {
		_validmoves.push_back(move(piece::code::w_rook, c, nw));
		od = nw;
		nw = od + 8;
	}
	od = c, nw = c - 8;
	while (od.getRow() - 1 == nw.getRow() && nw.isValid()) {
		_validmoves.push_back(move(piece::code::w_rook, c, nw));
		od = nw;
		nw = od - 8;
	}
	od = c, nw = c - 1;
	while (od.getRow() == nw.getRow() && nw.isValid()) {
		_validmoves.push_back(move(piece::code::w_rook, c, nw));
		od = nw;
		nw = od - 1;
	}
	od = c, nw = c + 1;
	while (od.getRow() == nw.getRow() && nw.isValid()) {
		_validmoves.push_back(move(piece::code::w_rook, c, nw));
		od = nw;
		nw = od + 1;
	}
}

void board::generateQueenMoves(coordinate c) {
	coordinate od = c, nw = c + 8;
	while (od.getRow() + 1 == nw.getRow() && nw.isValid()) {
		_validmoves.push_back(move(piece::code::w_quee, c, nw));
		od = nw;
		nw = od + 8;
	}
	od = c, nw = c - 8;
	while (od.getRow() - 1 == nw.getRow() && nw.isValid()) {
		_validmoves.push_back(move(piece::code::w_quee, c, nw));
		od = nw;
		nw = od - 8;
	}
	od = c, nw = c - 1;
	while (od.getRow() == nw.getRow() && nw.isValid()) {
		_validmoves.push_back(move(piece::code::w_quee, c, nw));
		od = nw;
		nw = od - 1;
	}
	od = c, nw = c + 1;
	while (od.getRow() == nw.getRow() && nw.isValid()) {
		_validmoves.push_back(move(piece::code::w_quee, c, nw));
		od = nw;
		nw = od + 1;
	}
	od = c, nw = c + 9;
	while (od.getRow() + 1 == nw.getRow() && nw.isValid()) {
		_validmoves.push_back(move(piece::code::w_quee, c, nw));
		od = nw;
		nw = od + 9;
	}
	od = c, nw = c + 7;
	while (od.getRow() + 1 == nw.getRow() && nw.isValid()) {
		_validmoves.push_back(move(piece::code::w_quee, c, nw));
		od = nw;
		nw = od + 7;
	}
	od = c, nw = c - 7;
	while (od.getRow() - 1 == nw.getRow() && nw.isValid()) {
		_validmoves.push_back(move(piece::code::w_quee, c, nw));
		od = nw;
		nw = od - 7;
	}
	od = c, nw = c - 9;
	while (od.getRow() - 1 == nw.getRow() && nw.isValid()) {
		_validmoves.push_back(move(piece::code::w_quee, c, nw));
		od = nw;
		nw = od - 9;
	}
}

void board::generateKingMoves(coordinate c) {
	coordinate od = c, nw = c + 8;
	if (od.getRow() + 1 == nw.getRow() && nw.isValid())
		_validmoves.push_back(move(piece::code::w_king, c, nw));

	od = c, nw = c + 9;
	if (od.getRow() + 1 == nw.getRow() && nw.isValid())
		_validmoves.push_back(move(piece::code::w_king, c, nw));

	od = c, nw = c + 7;
	if (od.getRow() + 1 == nw.getRow() && nw.isValid())
		_validmoves.push_back(move(piece::code::w_king, c, nw));

	od = c, nw = c - 8;
	if (od.getRow() - 1 == nw.getRow() && nw.isValid())
		_validmoves.push_back(move(piece::code::w_king, c, nw));

	od = c, nw = c - 9;
	if (od.getRow() - 1 == nw.getRow() && nw.isValid())
		_validmoves.push_back(move(piece::code::w_king, c, nw));

	od = c, nw = c - 7;
	if (od.getRow() - 1 == nw.getRow() && nw.isValid())
		_validmoves.push_back(move(piece::code::w_king, c, nw));

	od = c, nw = c - 1;
	if (od.getRow() == nw.getRow() && nw.isValid())
		_validmoves.push_back(move(piece::code::w_king, c, nw));

	od = c, nw = c + 1;
	if (od.getRow() == nw.getRow() && nw.isValid())
		_validmoves.push_back(move(piece::code::w_king, c, nw));

}