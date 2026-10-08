#pragma once

#include <cstddef>

#include <QPushButton>
#include <QString>
#include <QWidget>

namespace biv {
	// Кнопка клавиатуры хранит единый внешний вид для всех клавиш.
	class KeyBoardButton : public QPushButton {
		public:
			// Создаёт кнопку с подписью клавиши.
			KeyBoardButton(const QString& text = "", QWidget* parent = nullptr);
	};
}
