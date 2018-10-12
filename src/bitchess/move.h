#pragma once

#include <iostream>
#include <vector>
#include "bitchess.h"


enum direction {
	north,
	south,
	east,
	west,
	north_east,
	south_east,
	north_west,
	south_west
};

std::string getDirectionCode(direction dir);

class board::move {
public:
	move(piece p, coordinate from, coordinate to);

	piece getPiece() const { return piece((_data >> 6)% 16); };
	coordinate getFrom() const;
	coordinate getTo() const;
	uint16_t getRaw() {return _data;};
	uint16_t getHeader() { return ((_data >> 6) << 3) + getDirection(); };

	direction getDirection();

	friend std::ostream& operator<< (std::ostream& stream, board::move move);

	bool operator == (move rhs);
	bool operator != (move rhs);

	friend bool operator <(board::move m, board::move g);
	friend bool operator >(board::move m, board::move g);

	uint8_t distance();

	bool isDiagnal();

	private:
		uint16_t _data;
};

