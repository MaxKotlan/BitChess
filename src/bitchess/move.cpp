//
// Created by Konstantin Gredeskoul on 5/14/17.
//

#include "move.h"

board::move::move(piece p, coordinate from, coordinate to) : _data(0) {
	_data += uint16_t(p);
	_data += (uint16_t(from) << 4);
	_data += (uint16_t(to) << 10);
};


board::coordinate board::move::getFrom(){ 
	return ((_data >> 4) % 64); 
};

board::coordinate board::move::getTo(){ 
	return ((_data >> 10) % 64); 
};