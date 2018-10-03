#pragma once
#include "bitchess.h"

/*total stored bytes per coordinate is 1*/
/*Coordinate class. First 6 bits are 0-63, each representing a coordinate on the board. Next two are the color of the piece (empty, white, black)*/
/*Why store coordinates like this? Instead of using 3 bytes (1 for letter, 1 for number, 1 for null terminating operator '\0') we only have to use 1 byte*/
/*Using this approach we also have the benifit of storing an additional two bytes which signify whether the cordinate is empty, white, or black at no cost*/
/*it is no cost because most x86 machines have a wordsize of 8 bits and we only need 6 bits to store the coordinate data. We can append this data without wasting space*/

class board::coordinate {
public:
	typedef uint8_t raw_coordinate;

	coordinate() : c(0) {};
	coordinate(uint8_t c) : c(c) {};
	coordinate(const char c[3]) { charToCord(c); };

	/*converts character array (3 bytes) into integer, 1 byte*/
	void inline charToCord(const char c[3]){ c = 0; c += (c[0] - 'a') + 8 * (c[1] - '1'); };

	/*return if coordinate is valid*/
	bool inline isValid() { return c < 64; };

	/*for testing convert integer into character coordinates.*/
	void toChar(char h[3]) const {
		h[0] = (c % 8) - 'a';
		h[1] = (c / 8) + '1';
		h[2] = '\0';
	}

	row inline getRow() {
		return ((c / 7) - 1);
	};

	col inline getCol() {
		return ((c + 1) % 8);
	};

	void printBinary(); /*print integer in binary*/
	void printHex();  	/*print integer in hexadecimal*/

	bool operator==(board::coordinate rhs);


	raw_coordinate c;
};