#include "qt_game_map.hpp"

#include <QKeyEvent>
#include <QDebug>
#include <QPainter>
#include <QStringList>

#include <algorithm>

using biv::QtGameMap;

namespace {
	const QStringList sprite_paths = {
		QStringLiteral(":/sprites/mario.svg"),
		QStringLiteral(":/sprites/enemy.svg"),
		QStringLiteral(":/sprites/enemy.svg"),
		QStringLiteral(":/sprites/enemy.svg"),
		QStringLiteral(":/sprites/brick.svg"),
		QStringLiteral(":/sprites/question.svg"),
		QStringLiteral(":/sprites/coin.svg"),
		QStringLiteral(":/sprites/platform.svg"),
		QStringLiteral(":/sprites/ground.svg")
	};
	const QString empty_block_path = QStringLiteral(":/sprites/empty_block.svg");
	const QString final_ship_path = QStringLiteral(":/sprites/final_ship.svg");
}

QtGameMap::QtGameMap(int height, int width, Game* game)
	: QWidget(nullptr), GameMap(height, width), game(game), map_width(width) {
	for (std::size_t i = 0; i < sprites.size(); ++i) {
		sprites[i].load(sprite_paths.at(static_cast<qsizetype>(i)));
		if (sprites[i].isNull()) {
			qWarning() << "Unable to load Qt sprite:" << sprite_paths.at(static_cast<qsizetype>(i));
		}
	}
	empty_block_sprite.load(empty_block_path);
	final_ship_sprite.load(final_ship_path);
	setWindowTitle(QStringLiteral("Super Mario"));
	setFocusPolicy(Qt::StrongFocus);
	resize(1120, 640);
	show();
}

void QtGameMap::add_obj(biv::QtUIObject* object) {
	objects.push_back(object);
}

void QtGameMap::remove_obj(biv::QtUIObject* object) {
	objects.erase(std::remove(objects.begin(), objects.end(), object), objects.end());
}

void QtGameMap::show() const noexcept {
	const_cast<QtGameMap*>(this)->QWidget::show();
	const_cast<QtGameMap*>(this)->update();
}

void QtGameMap::draw_sprite(QPainter& painter, const QtUIObject& object, const QRect& target) const {
	const QtObjectKind kind = object.get_kind();
	if (object.is_empty()) {
		if (!empty_block_sprite.isNull()) {
			painter.drawPixmap(target, empty_block_sprite, empty_block_sprite.rect());
		}
		return;
	}
	if (object.is_final()) {
		if (!final_ship_sprite.isNull()) {
			painter.drawPixmap(target, final_ship_sprite, final_ship_sprite.rect());
		}
		return;
	}
	const auto index = static_cast<std::size_t>(kind);
	if (index >= sprites.size() || sprites[index].isNull()) {
		return;
	}
	const QPixmap& sprite = sprites[index];
	const bool tile_sprite =
		kind == QtObjectKind::Box ||
		kind == QtObjectKind::FullBox ||
		kind == QtObjectKind::MovingPlatform ||
		kind == QtObjectKind::Ship;
	if (!tile_sprite) {
		painter.drawPixmap(target, sprite, sprite.rect());
		return;
	}
	const int tile_width = sprite_size;
	const int tile_height = sprite_size;
	for (int x = target.left(); x < target.right(); x += tile_width) {
		for (int y = target.top(); y < target.bottom(); y += tile_height) {
			const QRect tile(x, y,
				std::min(tile_width, target.right() - x),
				std::min(tile_height, target.bottom() - y));
			painter.drawPixmap(tile, sprite, sprite.rect());
		}
	}
}

void QtGameMap::paintEvent(QPaintEvent*) {
	QPainter painter(this);
	painter.setRenderHint(QPainter::SmoothPixmapTransform, false);
	painter.fillRect(rect(), QColor(142, 135, 224));

	float camera_x = 0;
	for (biv::QtUIObject* object : objects) {
		if (object->get_kind() == biv::QtObjectKind::Mario) {
			camera_x = object->get_left() * sprite_size - QWidget::width() / 2.0f;
			break;
		}
	}
	camera_x = std::max(0.0f, std::min(camera_x,
		static_cast<float>(map_width * sprite_size - QWidget::width())));

	const auto world_rect = [camera_x](int x, int y, int width, int height) {
		return QRect(
			x * QtGameMap::sprite_size - static_cast<int>(camera_x),
			y * QtGameMap::sprite_size,
			width * QtGameMap::sprite_size,
			height * QtGameMap::sprite_size
		);
	};
	painter.setPen(Qt::NoPen);
	painter.setBrush(QColor(246, 246, 246));
	painter.drawEllipse(world_rect(8, 4, 8, 3));
	painter.drawEllipse(world_rect(14, 3, 10, 4));
	painter.drawEllipse(world_rect(35, 6, 9, 3));
	painter.drawEllipse(world_rect(42, 5, 12, 4));
	painter.setBrush(QColor(91, 178, 38));
	painter.drawEllipse(world_rect(25, 22, 16, 8));
	painter.setBrush(QColor(62, 145, 35));
	painter.drawEllipse(world_rect(29, 21, 12, 7));

	painter.setPen(Qt::NoPen);
	for (biv::QtUIObject* object : objects) {
		auto* collisionable = dynamic_cast<biv::Collisionable*>(object);
		if (collisionable != nullptr && !collisionable->is_active()) {
			continue;
		}
		const QRect target(
			object->get_left() * sprite_size - static_cast<int>(camera_x),
			object->get_top() * sprite_size,
			(object->get_right() - object->get_left()) * sprite_size,
			(object->get_bottom() - object->get_top()) * sprite_size
		);
		draw_sprite(painter, *object, target);
	}
}

void QtGameMap::keyPressEvent(QKeyEvent*) {}
