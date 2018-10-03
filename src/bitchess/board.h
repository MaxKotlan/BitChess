
#pragma once

#include <iostream>

#include "piece.h"

using namespace std;

class board {
public:

	typedef uint8_t row;
	typedef uint8_t col;

	class coordinate;

	board();

	piece getPiece(coordinate c);

	void addPiece(piece p, coordinate c);

	void clear();
	void random();
	void print();

private:
	uint32_t _row[8];
};

#include "coordinate.h"