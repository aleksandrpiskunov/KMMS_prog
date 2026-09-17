#include "console_game_map.hpp"

#include "collisionable.hpp"

#include <algorithm>
#include <cstdio>
#include <iostream>

#ifdef LINUX_CONSOLE
	#include <ncurses.h>
#endif

using biv::ConsoleGameMap;

ConsoleGameMap::ConsoleGameMap(const int height, const int width, Game* game)
	: GameMap(height, width), game(game) {

	map = new char*[height];
	for (int i = 0; i < height; i++) {
		map[i] = new char[width + 1];
	}
		
	clear();
}

ConsoleGameMap::~ConsoleGameMap() {
	for (int i = 0; i < height; i++) {
		delete [] map[i];
	}
	delete [] map;
}

void ConsoleGameMap::add_obj(ConsoleUIObject* obj) {
	objs.push_back(obj);
}

void ConsoleGameMap::clear() noexcept {
	// Воздух
	for (int i = 0; i < width; i++) {
		map[0][i] = ' ';
	}
	map[0][width] = '\0';
	
	for (int i = 1; i < height - 3; i++) {
		std::sprintf(map[i], "%s", map[0]);
	}
	
	// Вода
	for (int i = 0; i < width; i++) {
		map[height - 3][i] = '~';
	}
	map[height - 3][width] = '\0';
	
	for (int i = height - 2; i < height; i++) {
		std::sprintf(map[i], "%s", map[height - 3]);
	}
}

void ConsoleGameMap::refresh() noexcept {
	clear();
	if (game != nullptr) {
		std::snprintf(map[0], width + 1, "COINS:%d ENEMIES:%d", game->get_coins_collected(), game->get_enemies_killed());
	}
	
	for (ConsoleUIObject* obj: objs) {
		auto collisionable = dynamic_cast<biv::Collisionable*>(obj);
		if (collisionable != nullptr && !collisionable->is_active()) {
			continue;
		}
		int left = obj->get_left();
		int top = obj->get_top();
		int right = obj->get_right();
		int bottom = obj->get_bottom();
		
		char brush = obj->get_brush();
		
		for (int i = left; i < right; i++) {
			for (int j = top; j < bottom; j++) {
				if (is_on_map(i, j)) {
					map[j][i] = brush;
				}
			}
		}
	}
}

void ConsoleGameMap::remove_obj(ConsoleUIObject* obj) {
	objs.erase(std::remove(objs.begin(), objs.end(), obj), objs.end());
}

void ConsoleGameMap::remove_objs() {
	objs.clear();
}

void ConsoleGameMap::show() const noexcept {
	#ifdef WINDOWS_CONSOLE
		for (int i = 0; i < height; i++) {
			std::cout << map[i];
		}
	#elif defined(LINUX_CONSOLE)
		int color_pair = 1;
		if (game != nullptr) {
			switch (game->get_screen_color()) {
				case biv::ScreenColor::BLUE:
					color_pair = 1;
					break;
				case biv::ScreenColor::RED:
					color_pair = 2;
					break;
				case biv::ScreenColor::GREEN:
					color_pair = 3;
					break;
			}
		}
		attrset(COLOR_PAIR(color_pair));
		for (int i = 0; i < height; i++) {
			//printw("%s", map[i]);
			move(i, 0); 
			addstr(map[i]);
		}
		attrset(A_NORMAL);
		::refresh();
	#endif
}
