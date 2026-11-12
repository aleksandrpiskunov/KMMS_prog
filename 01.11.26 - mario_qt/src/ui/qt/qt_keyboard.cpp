#include "qt_keyboard.hpp"

#include <QCoreApplication>
#include <QEvent>
#include <QKeyEvent>

using biv::QtKeyboard;

QtKeyboard::QtKeyboard(QCoreApplication* application) : application(application) {
	application->installEventFilter(this);
}

biv::UserInput QtKeyboard::get_user_input() {
	application->processEvents(QEventLoop::AllEvents, 1);
	if (exit) {
		return UserInput::EXIT;
	}
	if (jump) {
		jump = false;
		return UserInput::MARIO_JUMP;
	}
	if (left) {
		return UserInput::MAP_RIGHT;
	}
	if (right) {
		return UserInput::MAP_LEFT;
	}
	return UserInput::NO_INPUT;
}

void QtKeyboard::on() {}

void QtKeyboard::off() {
	left = false;
	right = false;
	jump = false;
	exit = false;
}

bool QtKeyboard::eventFilter(QObject*, QEvent* event) {
	if (event->type() != QEvent::KeyPress && event->type() != QEvent::KeyRelease) {
		return false;
	}
	auto* key_event = static_cast<QKeyEvent*>(event);
	const bool pressed = event->type() == QEvent::KeyPress;
	switch (key_event->key()) {
		case Qt::Key_A:
		case Qt::Key_Left:
			left = pressed;
			return true;
		case Qt::Key_D:
		case Qt::Key_Right:
			right = pressed;
			return true;
		case Qt::Key_Space:
		case Qt::Key_Up:
			if (pressed && !key_event->isAutoRepeat()) {
				jump = true;
			}
			return true;
		case Qt::Key_Q:
		case Qt::Key_Escape:
			if (pressed) {
				exit = true;
			}
			return true;
		default:
			return false;
	}
}
