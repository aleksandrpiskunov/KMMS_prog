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
	kill();
}

void Money::process_vertical_static_collision(Rect* obj) noexcept {
	// Деньги могут свалиться с корабля: Кто не поймал, тот не успел. 
	
	// Особенность модели вертикального передвижения в игре.
	if (vspeed > 0) {
		top_left.y -= vspeed;
		vspeed = 0;
	}
}
