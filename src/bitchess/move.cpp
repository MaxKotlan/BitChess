//
// Created by Konstantin Gredeskoul on 5/14/17.
//

#include "move.h"
#include <algorithm>
#include <fstream>

std::string getDirectionCode(direction dir) {
	switch (dir) {
	case north: return "NORTH"; break;
	case south: return "SOTUH"; break;
	case  east: return "EAST "; break;
	case  west: return "WEST "; break;
	case north_east: return "NEAST"; break;
	case south_east: return "SEAST"; break;
	case north_west: return "NEWST"; break;
	case south_west: return "SWEST"; break;
	default: return "UNDF";
	}
}

board::move::move(piece p, coordinate from, coordinate to) : _data(0) {
	_data += uint16_t(p) << 6;
	_data += (uint16_t(from) << 10);
	_data += (uint16_t(to));
};


board::coordinate board::move::getFrom() const{ 
	return ((_data >> 10) % 64); 
};

board::coordinate board::move::getTo() const{ 
	return ((_data) % 64); 
};

std::ostream& operator<< (std::ostream& stream, board::move out) {

	#ifdef linux

	     if (direction::north == out.getDirection())
		stream << "\033[1;31m";
	else if (direction::north_east == out.getDirection())
		stream << "\033[1;32m";
	else if (direction::north_west == out.getDirection())
		stream << "\033[1;33m";
	else if (direction::south == out.getDirection())
		stream << "\033[1;34m";
	else if (direction::south_east == out.getDirection())
		stream << "\033[1;35m";
	else if (direction::south_west == out.getDirection())
		stream << "\033[1;36m";
	else if (direction::east == out.getDirection())
		stream << "\033[1;37m";
	else if (direction::west == out.getDirection())
		stream << "\033[1;38m";

	#endif

	stream << std::hex << "0x" << out._data << " [" << piece::getHumanReadable(out.getPiece()).c_str() << ", " << out.getFrom().getDisplayCoordinates().c_str() << ", " << out.getTo().getDisplayCoordinates().c_str() << "]";
	stream << "\033[0m";
	return stream;
}

direction board::move::getDirection() {
	if (getPiece() == piece::b_knig || getPiece() == piece::w_knig)
		return direction::south;
	     if ((getTo() / 8 > getFrom() / 8) && ((getTo() - getFrom()) % 8 == 0))
		return direction::north;
	else if ((getTo() / 8 > getFrom() / 8) && ((getTo() - getFrom()) % 7 == 0))
		return direction::north_east;
	else if ((getTo() / 8 > getFrom() / 8) && ((getTo() - getFrom()) % 9 == 0))
		return direction::north_west;

	else if ((getTo() / 8 < getFrom() / 8) && ((getTo() - getFrom()) % 8 == 0))
		return direction::south;
	else if ((getTo() / 8 < getFrom() / 8) && ((getTo() - getFrom()) % 7 == 0))
		return direction::south_east;
	else if ((getTo() / 8 < getFrom() / 8) && ((getTo() - getFrom()) % 9 == 0))
		return direction::south_west;

	else if (getTo().getRow() == getFrom().getRow() && getTo() - getFrom() > 0)
		return direction::east;
	else if (getTo().getRow() == getFrom().getRow() && getTo() - getFrom() < 0)
		return direction::west;
	else
		return direction::south;
	/*
	else if (uint8_t(getTo().getRow()) > uint8_t(getFrom().getRow) && (getTo() - getFrom()) % 7)
		return direction::north_west;
	else if (uint8_t(getTo().getRow()) > uint8_t(getFrom().getRow) && (getTo() - getFrom()) % 9)
		return direction::north_east;
	else if (uint8_t(getTo().getRow()) < uint8_t(getFrom().getRow) && (getTo() - getFrom()) % 8)
		return direction::south;
	else if (uint8_t(getTo().getRow()) < uint8_t(getFrom().getRow) && (getTo() - getFrom()) % 7)
		return direction::south_west;
	else if (uint8_t(getTo().getRow()) < uint8_t(getFrom().getRow) && (getTo() - getFrom()) % 9)
		return direction::south_east;
	else if (getTo() - getFrom() > 0)
		return direction::east;
	else if (getTo() - getFrom() < 0)
		return direction::west;*/
}

/*Needs improvement*/
bool board::move::isDiagnal() {
	return (distance()%7 == 0 || distance()%9 == 0);
}

uint8_t board::move::distance() {
	coordinate from = getFrom();
	coordinate to = getTo();
	if (getFrom() > getTo()) return getFrom() - getTo();
	else return getTo() - getFrom();
}

bool board::move::operator == (board::move rhs) {
	return (_data == rhs._data);
}

bool board::move::operator != (board::move rhs) {
	return (_data != rhs._data);
}


bool operator <(board::move left, board::move right)
{
	return left.getRaw() < right.getRaw();
}

bool operator >(board::move left, board::move right)
{
	return left.getRaw() > right.getRaw();
}