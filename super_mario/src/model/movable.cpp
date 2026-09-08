#include "movable.hpp"

using biv::Movable;

Movable::Movable(
	const Coord& top_left, 
	const int width, const int height, 
	const float vspeed, const float hspeed
) {
	this->top_left = top_left;
	this->width = width;
	this->height = height;
	this->vspeed = vspeed;
	this->hspeed = hspeed;
}

float Movable::get_vspeed() const noexcept {
	return vspeed;
}

void Movable::jump() noexcept {
	if (vspeed == 0) {
		vspeed = JUMP_SPEED;
	}
}

void Movable::move_horizontal_offset(const float offset) noexcept {
	top_left.x += offset;
}

void Movable::move_vertical_offset(const float offset) noexcept {
	top_left.y += offset;
}

// ----------------------------------------------------------------------------
// 									VIRTUAL
// ----------------------------------------------------------------------------
void Movable::move_horizontally() noexcept {
	top_left.x += hspeed;
}

void Movable::move_vertically() noexcept {
	if (vspeed < MAX_V_SPEED) {
		vspeed += V_ACCELERATION;
	}
	top_left.y += vspeed;
}
