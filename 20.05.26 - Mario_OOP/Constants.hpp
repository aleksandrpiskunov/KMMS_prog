#pragma once

namespace pav {
	inline constexpr int MAP_WIDTH = 80;
	inline constexpr int MAP_HEIGHT = 25;

	inline constexpr float GRAVITY = 0.06f;
	inline constexpr float ITEM_BOUNCE_SPEED = -0.7f;
	inline constexpr int COLOR_DEAD = 2;
	inline constexpr int COLOR_COMPLETE = 3;
	inline constexpr int COLOR_NORMAL = 1;
	inline constexpr char MYSTERY_BLOCK = '?';
	inline constexpr char EMPTY_BLOCK = '-';
	inline constexpr char EXIT_BLOCK = '+';
	inline constexpr char PLAYER = '@';
	inline constexpr char COLLECTIBLE = '$';
	inline constexpr char ENEMY = 'o';
}
