
#pragma once

#include <iostream>

#include "piece.h"

using namespace std;

class board {
public:

	typedef int8_t row;
	typedef int8_t col;

	class coordinate;

	board();

	piece getPiece(coordinate c);

	void addPiece(piece p, coordinate c);

	void printRaw();
	void printUTF();

	void clear();
	void random();
	void print();

private:
	uint32_t _row[8];
};

#include "coordinate.h"