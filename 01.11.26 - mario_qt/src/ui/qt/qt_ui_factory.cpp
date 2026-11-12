#include "qt_ui_factory.hpp"

#include <algorithm>

using biv::QtUIFactory;

QtUIFactory::~QtUIFactory() {
	clear_data();
	delete game_map;
}

void QtUIFactory::clear_data() {
	game->remove_objs();
	if (game_map != nullptr) {
		game_map->remove_objs();
	}
	for (biv::QtUIObject* object : objects) {
		delete object;
	}
	objects.clear();
	mario = nullptr;
}

template<class T, class... Args>
T* QtUIFactory::add_object(Args&&... args) {
	T* object = new T(std::forward<Args>(args)...);
	objects.push_back(object);
	game_map->add_obj(object);
	return object;
}

void QtUIFactory::create_box(const Coord& p, int w, int h) {
	auto* object = add_object<QtBox>(p, w, h);
	game->add_map_movable(object);
	game->add_static_obj(object);
}
void QtUIFactory::create_enemy(const Coord& p, int w, int h) {
	auto* object = add_object<QtEnemy>(p, w, h);
	game->add_map_movable(object); game->add_movable(object); game->add_collisionable(object);
}
void QtUIFactory::create_flyable_enemy(const Coord& p, int w, int h, int fh, int fr) {
	auto* object = add_object<QtFlyableEnemy>(p, w, h, fh, fr);
	game->add_map_movable(object); game->add_movable(object); game->add_collisionable(object);
}
void QtUIFactory::create_jumping_enemy(const Coord& p, int w, int h) {
	auto* object = add_object<QtJumpingEnemy>(p, w, h);
	game->add_map_movable(object); game->add_movable(object); game->add_collisionable(object);
}
void QtUIFactory::create_full_box(const Coord& p, int w, int h) {
	auto* object = add_object<QtFullBox>(p, w, h, this);
	game->add_collisionable(object); game->add_map_movable(object); game->add_static_obj(object);
}
void QtUIFactory::create_mario(const Coord& p, int w, int h) {
	if (mario != nullptr) {
		game->remove_collisionable(mario); game->remove_movable(mario); game->remove_mario();
		game_map->remove_obj(mario);
		objects.erase(std::remove(objects.begin(), objects.end(), mario), objects.end());
		delete mario;
	}
	mario = add_object<QtMario>(p, w, h);
	game->add_collisionable(mario); game->add_movable(mario); game->add_mario(mario);
}
void QtUIFactory::create_money(const Coord& p, int w, int h) {
	auto* object = add_object<QtMoney>(p, w, h);
	game->add_map_movable(object); game->add_movable(object); game->add_collisionable(object);
}
void QtUIFactory::create_moving_platform(const Coord& p, int w, int h, int r) {
	auto* object = add_object<QtMovingPlatform>(p, w, h, r);
	game->add_collisionable(object); game->add_map_movable(object); game->add_movable(object); game->add_static_obj(object);
}
void QtUIFactory::create_ship(const Coord& p, int w, int h) {
	auto* object = add_object<QtShip>(p, w, h);
	game->add_map_movable(object); game->add_static_obj(object);
}
void QtUIFactory::create_final_ship(const Coord& p, int w, int h) {
	auto* object = add_object<QtShip>(p, w, h);
	object->set_final(true);
	game->add_map_movable(object); game->add_static_obj(object);
}
biv::GameMap* QtUIFactory::get_game_map(int h, int w) {
	if (game_map == nullptr) {
		game_map = new QtGameMap(h, w, game);
	}
	return game_map;
}
biv::Mario* QtUIFactory::get_mario() {
	return mario;
}
