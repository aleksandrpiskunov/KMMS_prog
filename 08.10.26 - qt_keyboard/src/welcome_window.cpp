#include "welcome_window.hpp"

#include <QPushButton>
#include <QVBoxLayout>

using biv::WelcomeWindow;

WelcomeWindow::WelcomeWindow(QWidget* parent) : QWidget(parent) {
	// Задаём размеры и название отдельного стартового окна приложения.
	setFixedSize(520, 300);
	setWindowTitle("Грустная Клавиатура");

	// Кнопка является единственным действием на приветственном экране.
	QPushButton* keyboard_button = new QPushButton("Перейти к клавиатуре", this);
	keyboard_button->setMinimumHeight(70);
	keyboard_button->setFont(QFont("Roboto", 20));

	// Вертикальный layout центрирует кнопку внутри окна.
	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->addStretch();
	layout->addWidget(keyboard_button);
	layout->addStretch();

	// Соединение сигнала кнопки с сигналом окна передаёт событие в main.
	connect(keyboard_button, &QPushButton::clicked, this, &WelcomeWindow::keyboard_requested);
}