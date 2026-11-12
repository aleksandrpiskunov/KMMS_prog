#include "console_ui_obj_rect_adapter.hpp"

using biv::ConsoleUIObjectRectAdapter;

ConsoleUIObjectRectAdapter::ConsoleUIObjectRectAdapter(
	const Coord& top_left, const int width, const int height
) {
	this->top_left = top_left;
	this->width = width;
	this->height = height;
}

int ConsoleUIObjectRectAdapter::get_bottom() const noexcept {
	return Rect::get_bottom();
}

int ConsoleUIObjectRectAdapter::get_height() const noexcept {
	return Rect::get_height();
}

int ConsoleUIObjectRectAdapter::get_left() const noexcept {
	return Rect::get_left();
}

int ConsoleUIObjectRectAdapter::get_right() const noexcept {
	return Rect::get_right();
}

int ConsoleUIObjectRectAdapter::get_top() const noexcept {
	return Rect::get_top();
}