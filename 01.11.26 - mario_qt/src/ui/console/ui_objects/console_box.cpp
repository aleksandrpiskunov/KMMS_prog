#include "console_box.hpp"

using biv::ConsoleBox;

ConsoleBox::ConsoleBox(const Coord& top_left, const int width, const int height) 
	: Box(top_left, width, height) {}

char ConsoleBox::get_brush() const noexcept {
	return '-';
}
