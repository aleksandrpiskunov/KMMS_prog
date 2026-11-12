#include "game_map.hpp"

using biv::GameMap;

GameMap::GameMap(const int height, const int width) 
	: height(height), width(width) {}

bool GameMap::is_below_map(const int y) const noexcept {
	return y > height;
}
		
bool GameMap::is_on_map(const int x, const int y) const noexcept {
	return x >=0 && x < width && y >= 0 && y < height;
}
