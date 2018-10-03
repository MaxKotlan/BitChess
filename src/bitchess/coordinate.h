#pragma once
#include "bitchess.h"

/*total stored bytes per coordinate is 1*/
/*Coordinate class. First 6 bits are 0-63, each representing a coordinate on the board. Next two are the color of the piece (empty, white, black)*/
/*Why store coordinates like this? Instead of using 3 bytes (1 for letter, 1 for number, 1 for null terminating operator '\0') we only have to use 1 byte*/
/*Using this approach we also have the benifit of storing an additional two bytes which signify whether the cordinate is empty, white, or black at no cost*/
/*it is no cost because most x86 machines have a wordsize of 8 bits and we only need 6 bits to store the coordinate data. We can append this data without wasting space*/

class board::coordinate {
public:
	coordinate() : cord(0) {};
	coordinate(uint8_t c) : cord(c) {};
	coordinate(const char c[3]) { charToCord(c); };

	/*converts character array (3 bytes) into integer, 1 byte*/
	uint8_t charToCord(const char c[3]) {
		cord = 0;
		cord += ((uint8_t)(c[0] - 'a')) + 8 * (uint8_t)(c[1] - '1');
		return cord;
	};

	/*return if coordinate is valid*/
	bool inline isValid() { return cord < 64; };

	/*for testing convert integer into character coordinates.*/
	char* toChar(char c[3]) const {
		c[0] = (cord % 8) + 'a';
		c[1] = (cord / 8) + '1';
		c[2] = '\0';
		return c;
	}

	/*Returns True if coordinate is adjacent to the left edge of the board*/
	bool isLeftEdge() {
		return (cord + 1) % 8 == 0;
	}

	/*Returns True if coordinate is adjacent to the right edge of the board*/
	bool isRightEdge() {
		return (cord) % 8 == 0;
	}

	board::row getRow() {
		return (cord + 1) / 8;
	}

	board::col getCol() {
		return (cord) % 8;
	}


	/*print binary of integer*/
	void printBinary();

	/*print hex of integer*/
	void printHex();

	operator uint8_t() { return uint8_t(cord); };

	//friend coordinate operator + (const coordinate& lhs, const coordinate& rhs);
	//friend coordinate operator - (const coordinate& lhs, const coordinate& rhs);
	//friend std::ostream & operator << (std::ostream &out, const coordinate &c);
	bool operator == (const coordinate& rhs);
	bool operator != (const coordinate& rhs);


	uint8_t cord;
};
