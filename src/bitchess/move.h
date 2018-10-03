#pragma once

#include <iostream>
#include "bitchess.h"


class board::move {
	public:
		move(piece p, coordinate from, coordinate to);

		piece getPiece() { return piece( _data % 16 ); };
		
		coordinate getFrom();
		coordinate getTo();

	private:
		uint16_t _data;
};

