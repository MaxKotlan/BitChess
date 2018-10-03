#include "tests.h"
#include "bitchess.h"

void testcoordinate() {
	typedef board::coordinate coordinate;
	std::cout << "Testing Coordinate Mapping";
	{
		//coordinate a(0); coordinate b("a1");

	//	assert( a == b );
	}
	{
		coordinate j(1);
		coordinate c(10);
		coordinate k("a1");

		assert(k.getRow() == 0);
		assert(k.getCol() == 0);
		assert(j.getRow() == 0);
		assert(j.getCol() == 1);
		assert(c.getRow() == 1);
		assert(c.getCol() == 2);
	}
	{
		assert(coordinate("a1").cord == 0);
		assert(coordinate("b1").cord == 1);
		assert(coordinate("c1").cord == 2);
		assert(coordinate("d1").cord == 3);
		assert(coordinate("e1").cord == 4);
		assert(coordinate("f1").cord == 5);
		assert(coordinate("g1").cord == 6);
		assert(coordinate("h1").cord == 7);
	}
	{
		assert(coordinate("a2").cord ==  8);
		assert(coordinate("b2").cord ==  9);
		assert(coordinate("c2").cord == 10);
		assert(coordinate("d2").cord == 11);
		assert(coordinate("e2").cord == 12);
		assert(coordinate("f2").cord == 13);
		assert(coordinate("g2").cord == 14);
		assert(coordinate("h2").cord == 15);
	}
	{
		assert(coordinate("a3").cord == 16);
		assert(coordinate("b3").cord == 17);
		assert(coordinate("c3").cord == 18);
		assert(coordinate("d3").cord == 19);
		assert(coordinate("e3").cord == 20);
		assert(coordinate("f3").cord == 21);
		assert(coordinate("g3").cord == 22);
		assert(coordinate("h3").cord == 23);
	}
	{
		assert(coordinate("a4").cord == 24);
		assert(coordinate("b4").cord == 25);
		assert(coordinate("c4").cord == 26);
		assert(coordinate("d4").cord == 27);
		assert(coordinate("e4").cord == 28);
		assert(coordinate("f4").cord == 29);
		assert(coordinate("g4").cord == 30);
		assert(coordinate("h4").cord == 31);
	}
	{
		assert(coordinate("a5").cord == 32);
		assert(coordinate("b5").cord == 33);
		assert(coordinate("c5").cord == 34);
		assert(coordinate("d5").cord == 35);
		assert(coordinate("e5").cord == 36);
		assert(coordinate("f5").cord == 37);
		assert(coordinate("g5").cord == 38);
		assert(coordinate("h5").cord == 39);
	}
	{
		assert(coordinate("a6").cord == 40);
		assert(coordinate("b6").cord == 41);
		assert(coordinate("c6").cord == 42);
		assert(coordinate("d6").cord == 43);
		assert(coordinate("e6").cord == 44);
		assert(coordinate("f6").cord == 45);
		assert(coordinate("g6").cord == 46);
		assert(coordinate("h6").cord == 47);
	}
	{
		assert(coordinate("a7").cord == 48);
		assert(coordinate("b7").cord == 49);
		assert(coordinate("c7").cord == 50);
		assert(coordinate("d7").cord == 51);
		assert(coordinate("e7").cord == 52);
		assert(coordinate("f7").cord == 53);
		assert(coordinate("g7").cord == 54);
		assert(coordinate("h7").cord == 55);
	}
	{
		assert(coordinate("a8").cord == 56);
		assert(coordinate("b8").cord == 57);
		assert(coordinate("c8").cord == 58);
		assert(coordinate("d8").cord == 59);
		assert(coordinate("e8").cord == 60);
		assert(coordinate("f8").cord == 61);
		assert(coordinate("g8").cord == 62);
		assert(coordinate("h8").cord == 63);
	}
	{
		assert(coordinate("a1").cord == 0);
		assert(coordinate("b1").cord == 1);
		assert(coordinate("c1").cord == 2);
		assert(coordinate("d1").cord == 3);
		assert(coordinate("e1").cord == 4);
		assert(coordinate("f1").cord == 5);
		assert(coordinate("g1").cord == 6);
		assert(coordinate("h1").cord == 7);
	}
	{

	}
}