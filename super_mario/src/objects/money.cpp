#include "money.hpp"

#include "map_movable.hpp"

using biv::Money;

Money::Money(const Coord& top_left, const int width, const int height) 
	: RectMapMovableAdapter(top_left, width, height) {
	vspeed = 0;
	hspeed = 0.2;
}

biv::Rect Money::get_rect() const noexcept {
	return {top_left, width, height};
}

biv::Speed Money::get_speed() const noexcept {
	return {vspeed, hspeed};
}

void Money::process_horizontal_static_collision(Rect* obj) noexcept {
	hspeed = -hspeed;
	move_horizontally();
}

void Money::process_mario_collision(Collisionable* mario) noexcept {
	(void)mario;
	vspeed = 0.15f;
	hspeed = 0.0f;
	kill();
}

void Money::process_vertical_static_collision(Rect* obj) noexcept {
	if (vspeed > 0) {
		top_left.y -= vspeed;
		vspeed = 0;
	}
}

void Money::process_platform_collision(Collisionable* platform) noexcept {
	if (platform == nullptr) {
		return;
	}

	if (get_speed().v < 0) {
		return;
	}

	const Rect platform_rect = platform->get_rect();
	if (get_rect().get_bottom() < platform_rect.get_top() - 1 || get_rect().get_bottom() > platform_rect.get_top() + 1) {
		return;
	}

	move_horizontal_offset(platform->get_speed().h);
}
