#pragma once

#include <vector>

#include "qt_game_map.hpp"
#include "qt_objects.hpp"
#include "ui_factory.hpp"

namespace biv {
	class QtUIFactory final : public UIFactory {
		private:
			QtGameMap* game_map = nullptr;
			QtMario* mario = nullptr;
			std::vector<QtUIObject*> objects;

			template<class T, class... Args>
			T* add_object(Args&&... args);

		public:
			// Сохраняет ссылку на контроллер, которому фабрика регистрирует модели.
			explicit QtUIFactory(Game* game) : UIFactory(game) {}
			~QtUIFactory();
			void clear_data() override;
			void create_box(const Coord&, int, int) override;
			void create_enemy(const Coord&, int, int) override;
			void create_flyable_enemy(const Coord&, int, int, int, int) override;
			void create_jumping_enemy(const Coord&, int, int) override;
			void create_full_box(const Coord&, int, int) override;
			void create_mario(const Coord&, int, int) override;
			void create_money(const Coord&, int, int) override;
			void create_moving_platform(const Coord&, int, int, int) override;
			void create_ship(const Coord&, int, int) override;
			void create_final_ship(const Coord&, int, int) override;
			GameMap* get_game_map(int, int) override;
			Mario* get_mario() override;
	};
}
