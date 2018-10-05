
#pragma once

#include <iostream>
#include <vector>

#include "piece.h"

using namespace std;

class board {
public:

	typedef int8_t row;
	typedef int8_t col;

	class coordinate;
	class move;


	board();

	piece getPiece(coordinate c);

	void addPiece(piece p, coordinate c);
	void movePiece(coordinate c, coordinate d);
	void removePiece(coordinate c);
	void promotePiece(piece p, coordinate c);

	void printRaw();
	void printUTF();

	void generateValidMoves();
	void printValidMoves();

	void clear();
	void random();
	void print();

	bool operator == (const board& rhs);
	bool operator != (const board& rhs);

private:
	uint32_t _row[8];
	std::vector<move> _validmoves;
};

#include "coordinate.h"
#include "move.h"