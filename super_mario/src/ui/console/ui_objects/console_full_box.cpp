#include "console_full_box.hpp"

using biv::ConsoleFullBox;

ConsoleFullBox::ConsoleFullBox(
	const Coord& top_left, 
	const int width, const int height,
	UIFactory* ui_factory
) : FullBox(top_left, width, height, ui_factory) {}

char ConsoleFullBox::get_brush() const noexcept {
	if (is_active_) {
		return '?';
	} else {
		return '-';
	}
}
