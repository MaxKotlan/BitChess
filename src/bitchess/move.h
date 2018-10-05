#pragma once

#include <iostream>
#include "bitchess.h"


class board::move {
	public:
		move(piece p, coordinate from, coordinate to);

		piece getPiece() const { return piece( _data % 16 ); };
		
		coordinate getFrom() const;
		coordinate getTo() const;

		friend std::ostream& operator<< (std::ostream& stream, const board::move& matrix);

	private:
		uint16_t _data;
};

