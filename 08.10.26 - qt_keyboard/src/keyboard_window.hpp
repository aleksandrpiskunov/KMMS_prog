#pragma once

#include <cstddef>

#include <QKeyEvent>
#include <QTextEdit>
#include <QWidget>

#include "keyboard.hpp"

namespace biv {
	// Главное окно принимает физические нажатия и отображает их на виртуальной клавиатуре.
	class KeyBoardWindow : public QWidget {
		private:
			// Поле показывает накопленный пользователем текст.
			QTextEdit* display;
			// Виджет виртуальной клавиатуры подсвечивает обработанную клавишу.
			KeyBoard* keyboard;

		private slots:
			// Слоты принимают сигналы мыши и физической клавиатуры через один интерфейс.
			void append_text(const QString& text);
			void remove_last_character();
			void insert_line_break();

		public:
			// Создаёт разметку окна клавиатуры.
			KeyBoardWindow(QWidget* parent = nullptr);
			
		protected:
			// Обрабатывает физические нажатия клавиш.
			void keyPressEvent(QKeyEvent* event) override;
	};
}
