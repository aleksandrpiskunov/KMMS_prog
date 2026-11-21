/**
	Игровой цикл - это обощённое представление потока событий, происходящих в игре.

	Игровой цикл:
		1. Установка параметров игры
		2. Получение пользовательского ввода
		3. Обновление внутреннего состояния игры
		4. Обновление изображения на экране
		5. Проверка того, не окончена ли игра

		*** Если игра не окончена, то возвращаемся в пункт № 2.

		6. Завершение
		
	- Какие архитектурные принципы применены при реализации игры?
	: MVC 
	
	- На основе какого приципа ООП построен алгоритм игры?
	: Полиморфизм
	- Какими элементами языка С++ реализуется этот принцип?
	: Виртаульными функциями
	- Приведите примеры кода, отображающие этот прицип.
*/
#include <thread>

#include "console_ui_factory.hpp"
#include "first_level.hpp"
#include "game.hpp"
#include "game_level.hpp"
#include "game_map.hpp"
#include "keyboard.hpp"
#include "mario.hpp"
#include "os_control_settings.hpp"
#include "ui_factory.hpp"

#ifdef QT_UI
	#include <QApplication>
	#include "qt_app_factory.hpp"
	#include "qt_ui_factory.hpp"
#endif

#ifdef WINDOWS_CONSOLE
	#include "windows_app_factory.hpp"
#elif defined(LINUX_CONSOLE)
	#include "linux_app_factory.hpp"
	#include "ncurses.h"
#endif

int main(int argc, char** argv) {
	// 1. Установка параметров игры
	using namespace std::chrono_literals;
	using clock_type = std::chrono::steady_clock;
	
	const int map_height = 30;
	const int map_weight = 200;
	auto frame_delay = std::chrono::milliseconds(0);
	
#ifdef QT_UI
	QApplication application(argc, argv);
	biv::QtAppFactory app_factory(&application);
#elif defined(WINDOWS_CONSOLE)
	biv::WindowsAppFactory app_factory;
#elif defined(LINUX_CONSOLE)
	biv::LinuxAppFactory app_factory(map_height, map_weight);
#endif

#ifdef QT_UI
	frame_delay = std::chrono::milliseconds(20);
#elif defined(WINDOWS_CONSOLE)
	frame_delay = std::chrono::milliseconds(10);
#elif defined(LINUX_CONSOLE)
	frame_delay = std::chrono::milliseconds(20);
#endif

	biv::OSControlSettings* control_settings = app_factory.get_control_settings();
	biv::KeyBoard* keyboard = app_factory.get_keyboard();
	if (control_settings != nullptr) {
		control_settings->init();
	}
	keyboard->on();
	
	biv::Game game;
#ifdef QT_UI
	biv::UIFactory* ui_factory = new biv::QtUIFactory(&game);
#else
	biv::UIFactory* ui_factory = new biv::ConsoleUIFactory(&game);
#endif
	biv::GameMap* game_map = ui_factory->get_game_map(map_height, map_weight);
	biv::GameLevel* game_level = new biv::FirstLevel(ui_factory);
	biv::Mario* mario = ui_factory->get_mario();
	auto flash_screen = [&](biv::ScreenColor color, const std::chrono::milliseconds duration) {
		game.set_screen_color(color);
		const auto start = clock_type::now();
		while (clock_type::now() - start < duration) {
			game_map->refresh();
			if (control_settings != nullptr) {
				control_settings->set_cursor_start_position();
			}
			game_map->show();
			std::this_thread::sleep_for(frame_delay);
		}
		game.set_screen_color(biv::ScreenColor::BLUE);
	};
	
	biv::UserInput user_input;
	do {
		// 2. Получение пользовательского ввода	
		user_input = keyboard->get_user_input();
		switch (user_input) {
			case biv::UserInput::MAP_LEFT:
				mario->move_map_left();
				if (!game.check_static_collisions(mario)) {
					game.move_map_left();
				}
				mario->move_map_right();
				break;
			case biv::UserInput::MAP_RIGHT:
				mario->move_map_right();
				if (!game.check_static_collisions(mario)) {
					game.move_map_right();
				}
				mario->move_map_left();
				break;
			case biv::UserInput::MARIO_JUMP:
				mario->jump();
				break;
			case biv::UserInput::EXIT:
				game.finish();
				break;
			case biv::UserInput::NO_INPUT:
				break;
		}
		
		// 3. Обновление внутреннего состояния игры
		game.move_objs_horizontally();
		game.check_horizontally_static_collisions();

		game.move_objs_vertically();
		game.check_mario_collision();
		game.check_mov_platfrom_collision();
		game.check_vertically_static_collisions();
		
		if (
			game_map->is_below_map(mario->get_top())
			|| !mario->is_active()
		) {
			flash_screen(biv::ScreenColor::RED, 1000ms);
			game.reset_stats();
			keyboard->off();
			keyboard->on();
			game_level->restart();
			mario = ui_factory->get_mario();
		}
		
		if (game.is_level_end()) {
			if (!game_level->is_final()) {
				flash_screen(biv::ScreenColor::GREEN, 1000ms);
				game_level = game_level->get_next();
				mario = ui_factory->get_mario();
				keyboard->off();
				keyboard->on();
				game.start_level();
			} else {
				game.finish();
			}
		}
		
		// 4. Обновление изображения на экране
		game_map->refresh();
		if (control_settings != nullptr) {
			control_settings->set_cursor_start_position();
		}
		game_map->show();
		std::this_thread::sleep_for(frame_delay);
	} while (
		/* 5. Проверка того, не окончена ли игра */ 
		!game.is_finished()
	);
	
	// 6. Завершение
}
