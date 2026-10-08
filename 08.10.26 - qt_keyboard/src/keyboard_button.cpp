#include "keyboard_button.hpp"

#include <QSizePolicy>

using biv::KeyBoardButton;

KeyBoardButton::KeyBoardButton(const QString& text, QWidget* parent)
    : QPushButton(parent) {
	// Все клавиши используют одинаковый шрифт и растягиваются внутри layout.
	setFont(QFont("Roboto", 20));
	setText(text);
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}
