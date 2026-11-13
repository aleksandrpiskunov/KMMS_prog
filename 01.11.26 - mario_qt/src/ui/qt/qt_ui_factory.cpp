#include "qt_ui_factory.hpp"

#include <algorithm>

using biv::QtUIFactory;

QtUIFactory::~QtUIFactory() {
	// Освобождает Qt-представление и все созданные визуальные объекты.
	clear_data();
	delete game_map;
}

void QtUIFactory::clear_data() {
	// Удаляет объекты из контроллера и очищает их представление перед новым уровнем.
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
	// Создаёт Qt-обёртку модели, сохраняет её и добавляет в карту.
	T* object = new T(std::forward<Args>(args)...);
	objects.push_back(object);
	game_map->add_obj(object);
	return object;
}

void QtUIFactory::create_box(const Coord& p, int w, int h) {
	// Создаёт неподвижный блок и регистрирует его как препятствие.
	auto* object = add_object<QtBox>(p, w, h);
	game->add_map_movable(object);
	game->add_static_obj(object);
}
void QtUIFactory::create_enemy(const Coord& p, int w, int h) {
	// Создаёт обычного врага и подключает его к движению и столкновениям.
	auto* object = add_object<QtEnemy>(p, w, h);
	game->add_map_movable(object); game->add_movable(object); game->add_collisionable(object);
}
void QtUIFactory::create_flyable_enemy(const Coord& p, int w, int h, int fh, int fr) {
	// Создаёт летающего врага с параметрами его траектории.
	auto* object = add_object<QtFlyableEnemy>(p, w, h, fh, fr);
	game->add_map_movable(object); game->add_movable(object); game->add_collisionable(object);
}
void QtUIFactory::create_jumping_enemy(const Coord& p, int w, int h) {
	// Создаёт врага, чьё движение рассчитывает модель.
	auto* object = add_object<QtJumpingEnemy>(p, w, h);
	game->add_map_movable(object); game->add_movable(object); game->add_collisionable(object);
}
void QtUIFactory::create_full_box(const Coord& p, int w, int h) {
	// Создаёт блок с монетой и передаёт ему фабрику для игровой логики.
	auto* object = add_object<QtFullBox>(p, w, h, this);
	game->add_collisionable(object); game->add_map_movable(object); game->add_static_obj(object);
}
void QtUIFactory::create_mario(const Coord& p, int w, int h) {
	// Заменяет текущего Марио и регистрирует нового в контроллере.
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
	// Создаёт монету, управляемую физикой и столкновениями модели.
	auto* object = add_object<QtMoney>(p, w, h);
	game->add_map_movable(object); game->add_movable(object); game->add_collisionable(object);
}
void QtUIFactory::create_moving_platform(const Coord& p, int w, int h, int r) {
	// Создаёт платформу и подключает её к движению, физике и коллизиям.
	auto* object = add_object<QtMovingPlatform>(p, w, h, r);
	game->add_collisionable(object); 
	game->add_map_movable(object); 
	game->add_movable(object); 
	game->add_static_obj(object);
}
void QtUIFactory::create_ship(const Coord& p, int w, int h) {
	// Создаёт обычную часть платформы уровня.
	auto* object = add_object<QtShip>(p, w, h);
	game->add_map_movable(object); game->add_static_obj(object);
}
void QtUIFactory::create_final_ship(const Coord& p, int w, int h) {
	// Создаёт платформу-финиш и помечает её специальным состоянием.
	auto* object = add_object<QtShip>(p, w, h);
	object->set_final(true);
	game->add_map_movable(object); game->add_static_obj(object);
}
biv::GameMap* QtUIFactory::get_game_map(int h, int w) {
	// Лениво создаёт единственное Qt-окно карты и возвращает абстракцию GameMap.
	if (game_map == nullptr) {
		game_map = new QtGameMap(h, w, game);
	}
	return game_map;
}
biv::Mario* QtUIFactory::get_mario() {
	// Возвращает модель Марио для игрового цикла.
	return mario;
}
