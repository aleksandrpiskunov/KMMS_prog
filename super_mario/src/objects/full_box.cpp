#include "full_box.hpp"

using biv::FullBox;

FullBox::FullBox(
	const Coord& top_left, 
	const int width, const int height,
	UIFactory* ui_factory
) : Box(top_left, width, height), ui_factory(ui_factory) {}

biv::Rect FullBox::get_rect() const noexcept {
	return {top_left, width, height};
}

biv::Speed FullBox::get_speed() const noexcept {
	return {0, 0};
}

void FullBox::process_horizontal_static_collision(Rect* obj) noexcept {}

void FullBox::process_mario_collision(Collisionable* mario) noexcept {
	if (mario->get_speed().v < 0) {
		kill();
		ui_factory->create_money({top_left.x, top_left.y - 3}, 3, 2);
	}
}

void FullBox::process_vertical_static_collision(Rect* obj) noexcept {}
