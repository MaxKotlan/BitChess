#pragma once
#include <iostream>

class piece {
	public:
	
	static const uint8_t code_bits = 4;

	enum code {
		empty,
		w_pawn,
		w_knig,
		w_bish,
		w_rook,
		w_quee,
		w_king,
		b_pawn,
		b_knig,
		b_bish,
		b_rook,
		b_quee,
		b_king
	};
	
	piece(code t) : _code(t) {};
	piece(uint8_t t) : _code(static_cast<piece::code>(t)) {};

	static std::string getHumanReadable(piece::code piece) {
		switch (piece) {
			case empty: return "    "; break;
			case w_pawn: case b_pawn: return "PAWN"; break;
			case w_knig: case b_knig: return "KNIG"; break;
			case w_bish: case b_bish: return "BISH"; break;
			case w_rook: case b_rook: return "ROOK"; break;
			case w_quee: case b_quee: return "QUEE"; break;
			case w_king: case b_king: return "KING"; break;
			default: return "UNDF";
		}
	}

	static char16_t getUTF8(piece::code piece) {
		const char* cd = " ♙♘♗♖♕♔♟♞♝♜♛♚";
		return cd[piece];
	}

	operator uint32_t()    { return _code; };
	operator uint16_t()    { return _code; };
	operator uint8_t()     { return _code; };
	operator piece::code() { return _code; };

	private:
		code _code;
};