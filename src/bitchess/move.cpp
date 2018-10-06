//
// Created by Konstantin Gredeskoul on 5/14/17.
//

#include "move.h"

board::move::move(piece p, coordinate from, coordinate to) : _data(0) {
	_data += uint16_t(p);
	_data += (uint16_t(from) << 4);
	_data += (uint16_t(to) << 10);
};


board::coordinate board::move::getFrom() const{ 
	return ((_data >> 4) % 64); 
};

board::coordinate board::move::getTo() const{ 
	return ((_data >> 10) % 64); 
};

std::ostream& operator<< (std::ostream& stream, const board::move& out) {
	stream << std::hex << "0x" << out._data << " [" << piece::getHumanReadable(out.getPiece()).c_str() << ", " << out.getFrom().getDisplayCoordinates().c_str() << ", " << out.getTo().getDisplayCoordinates().c_str() << "]";
	return stream;
}
