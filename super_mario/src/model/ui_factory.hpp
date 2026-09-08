/**
	- Какому паттерну проектирования соответствует UIFactory?
	:Factory 
	- В каких случаях используется этот паттернн проектирования?
	: It makes changing current classes easier. It avoidin editing code in each part where we created instance of editad class. 
*/

#pragma once

#include "game.hpp"
#include "game_map.hpp"
#include "mario.hpp"

namespace biv {
	class UIFactory {
		protected:
			Game* game = nullptr;
			
		protected:
			UIFactory(Game* game) : game(game) {}

		public:
			virtual void clear_data() = 0;
			virtual void create_box(
				const Coord& top_left, const int width, const int height) = 0;
			virtual void create_enemy(
				const Coord& top_left, const int width, const int height) = 0;
			virtual void create_full_box(
				const Coord& top_left, const int width, const int height) = 0;
			virtual void create_mario(
				const Coord& top_left, const int width, const int height) = 0;
			virtual void create_money(
				const Coord& top_left, const int width, const int height) = 0;
			virtual void create_ship(
				const Coord& top_left, const int width, const int height) = 0;
			virtual GameMap* get_game_map(const int height, const int width) = 0;
			virtual Mario* get_mario() = 0;
	};
}
