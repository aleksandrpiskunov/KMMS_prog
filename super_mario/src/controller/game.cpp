#include "game.hpp"

#include <algorithm>

#include "enemy.hpp"
#include "flyable_enemy.hpp"
#include "jumping_enemy.hpp"
#include "money.hpp"

using biv::Game;

Game::Game() {}

void Game::add_collisionable(Collisionable* obj) {
	collisionable_objs.push_back(obj);
}

void Game::add_map_movable(MapMovable* obj) {
	map_movable_objs.push_back(obj);
}

void Game::add_mario(Mario* obj) {
	mario = obj;
}

void Game::add_movable(Movable* obj) {
	movable_objs.push_back(obj);
}

void Game::add_static_obj(Rect* obj) {
	static_objs.push_back(obj);
}

void Game::check_horizontally_static_collisions() noexcept {
	for (Collisionable* obj: collisionable_objs) {
		if (!obj->is_active()) {
			continue;
		}
		Rect* obj_rect = dynamic_cast<Rect*>(obj);
		for (Rect* static_obj: static_objs) {
			if (obj_rect == static_obj) {
				continue;
			}
			if (obj->has_collision(static_obj)) {
				obj->process_horizontal_static_collision(static_obj);
				break;
			}
		}
	}
}

void Game::check_mario_collision() {
	for (int i = 0; i < collisionable_objs.size(); i++) {
		Collisionable* obj = collisionable_objs[i];
		if (!obj->is_active()) {
			continue;
		}
		if (obj->has_collision(mario)) {
			obj->process_mario_collision(mario);
			if (!obj->is_active()) {
				if (dynamic_cast<Money*>(obj) != nullptr) {
					add_coin();
				} else if (
					dynamic_cast<Enemy*>(obj) != nullptr ||
					dynamic_cast<FlyableEnemy*>(obj) != nullptr
				) {
					add_enemy_kill();
				}
			}
			if (!mario->is_active()) {
				break;
			}
		}
	}
}

bool Game::check_static_collisions(Collisionable* obj) const noexcept {
	Rect* obj_rect = dynamic_cast<Rect*>(obj);
	for (Rect* static_obj: static_objs) {
		if (obj_rect == static_obj) {
			continue;
		}
		if (obj->has_collision(static_obj)) {
			return true;
		}
	}
	return false;
}

void Game::check_vertically_static_collisions() noexcept {
	if (mario->has_collision(static_objs[static_objs.size() - 1])) {
		is_level_end_ = true;
	}
	
	for (Collisionable* obj: collisionable_objs) {
		if (!obj->is_active()) {
			continue;
		}
		Rect* obj_rect = dynamic_cast<Rect*>(obj);
		for (Rect* static_obj: static_objs) {
			if (obj_rect == static_obj) {
				continue;
			}
			if (obj->has_collision(static_obj)) {
				obj->process_vertical_static_collision(static_obj);
				break;
			}
		}
	}
}

void Game::finish() noexcept {
	is_finished_ = true;
}

bool Game::is_finished() const noexcept {
	return is_finished_;
}

bool Game::is_level_end() const noexcept {
	return is_level_end_;
}

int Game::get_coins_collected() const noexcept {
	return coins_collected_;
}

int Game::get_enemies_killed() const noexcept {
	return enemies_killed_;
}

void Game::add_coin() noexcept {
	coins_collected_++;
}

void Game::add_enemy_kill() noexcept {
	enemies_killed_++;
}

void Game::reset_stats() noexcept {
	coins_collected_ = 0;
	enemies_killed_ = 0;
}

void Game::move_map_left() noexcept {
	for (MapMovable* obj: map_movable_objs) {
		obj->move_map_left();
	}
}

void Game::move_map_right() noexcept {
	for (MapMovable* obj: map_movable_objs) {
		obj->move_map_right();
	}
}

void Game::move_objs_horizontally() noexcept {
	for (Movable* obj: movable_objs) {

		obj->move_horizontally();
	}
}

void Game::move_objs_vertically() noexcept {
	for (Movable* obj: movable_objs) {
		obj->move_vertically();
	}
}

void Game::remove_collisionable(Collisionable* obj) {
	remove_obj(collisionable_objs, obj);
}

void Game::remove_map_movable(MapMovable* obj) {
	remove_obj(map_movable_objs, obj);
}

void Game::remove_mario() noexcept {
	mario = nullptr;
}

void Game::remove_movable(Movable* obj) {
	remove_obj(movable_objs, obj);
}

void Game::remove_objs() {
	collisionable_objs.clear();
	map_movable_objs.clear();
	movable_objs.clear();
	static_objs.clear();
	remove_mario();
}

void Game::remove_static_obj(Rect* obj) {
	remove_obj(static_objs, obj);
}

void Game::start_level() noexcept {
	is_level_end_ = false;
}

// ----------------------------------------------------------------------------
// 									PRIVATE
// ----------------------------------------------------------------------------
template<class T>
void Game::remove_obj(std::vector<T*>& container, T* obj) {
	container.erase(
		std::remove(
			container.begin(), container.end(), obj
		), 
		container.end()
	);
}
