#pragma once

#include <QWidget>
#include <QPainter>
#include <array>
#include <QPixmap>
#include <vector>

#include "game.hpp"
#include "game_map.hpp"
#include "qt_ui_object.hpp"

namespace biv {
	class QtGameMap final : public QWidget, public GameMap {
		private:
			static constexpr int sprite_size = 20;
			Game* game;
			int map_width;
			std::vector<QtUIObject*> objects;
			std::array<QPixmap, 9> sprites;
			QPixmap empty_block_sprite;
			QPixmap final_ship_sprite;

			void draw_sprite(QPainter& painter, const QtUIObject& object, const QRect& target) const;

		public:
			QtGameMap(int height, int width, Game* game);
			void add_obj(QtUIObject* object);
			// Qt очищает фон в paintEvent, поэтому отдельная очистка не нужна.
			void clear() noexcept override {}
			// Просит Qt вызвать paintEvent на следующем проходе событий.
			void refresh() noexcept override { update(); }
			void remove_obj(QtUIObject* object);
			// Удаляет все ссылки на объекты текущего уровня.
			void remove_objs() override { objects.clear(); }
			void show() const noexcept override;

		protected:
			void paintEvent(QPaintEvent*) override;
			void keyPressEvent(QKeyEvent*) override;
	};
}
