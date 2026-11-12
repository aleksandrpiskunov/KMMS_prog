#include "console_mario.hpp"

using biv::ConsoleMario;

ConsoleMario::ConsoleMario(const Coord& top_left, const int width, const int height) 
	: Mario(top_left, width, height) {}

char ConsoleMario::get_brush() const noexcept {
	return '@';
}
