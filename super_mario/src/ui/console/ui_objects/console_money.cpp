#include "console_money.hpp"

using biv::ConsoleMoney;

ConsoleMoney::ConsoleMoney(const Coord& top_left, const int width, const int height) 
	: Money(top_left, width, height) {}

char ConsoleMoney::get_brush() const noexcept {
	return '$';
}
