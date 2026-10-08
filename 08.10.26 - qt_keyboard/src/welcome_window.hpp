#pragma once

#include <QWidget>

namespace biv {
	// Окно приветствия запускает переход к экрану виртуальной клавиатуры.
	class WelcomeWindow : public QWidget {
		Q_OBJECT

		public:
			// Создаёт окно с заголовком и кнопкой перехода.
			WelcomeWindow(QWidget* parent = nullptr);

		signals:
			// Сигнал сообщает приложению, что пользователь готов открыть клавиатуру.
			void keyboard_requested();
	};
}