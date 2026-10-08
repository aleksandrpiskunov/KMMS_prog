#pragma once

#include <cstddef>
#include <unordered_map>

#include <QGridLayout>
#include <QWidget>

#include "keyboard_button.hpp"
#include "keyboard_data.hpp"
#include "key_data.hpp"

namespace biv {
	// Виджет строит виртуальную клавиатуру и управляет её кнопками.
	class KeyBoard : public QWidget {
		Q_OBJECT

		private:
			// Ширина одной условной клавиши используется для выравнивания рядов.
			const int button_width;
			// Кнопки индексируются кодом физической клавиши.
			std::unordered_map<int, KeyBoardButton*> buttons;
			
			// Данные раскладки отделены от визуального построения клавиатуры.
			KeyBoardData* keyboard_data;
			// Специальные кнопки хранятся отдельно, потому что у них нет кода из раскладки.
			KeyBoardButton* backspace_button;
			KeyBoardButton* enter_button;
			KeyBoardButton* space_button;
		
		public:
			// Создаёт клавиатуру заданной ширины.
			KeyBoard(const int width, QWidget* parent = nullptr);
			
			// Запускает короткую анимацию нажатия виртуальной кнопки.
			void animate_button(const int code);
			// Возвращает текст кнопки по коду физической клавиши.
			QString get_key_text(const int code) const;
			// Проверяет, должна ли клавиша участвовать в вводе текста.
			bool is_key_allowed(const int code) const noexcept;
			// Воспроизводят нажатие специальных кнопок физической клавиатурой.
			void animate_backspace();
			void animate_enter();
			void animate_space();

		signals:
			// Сигнал передаёт символы, которые нужно добавить в поле текста.
			void text_key_pressed(const QString& text);
			// Сигналы специальных клавиш передаются окну для изменения текста.
			void backspace_pressed();
			void enter_pressed();
			
		private:
			// Добавляет один ряд кнопок в переданный grid layout.
			void create_buttons(
				const std::vector<KeyData>& data, 
				QGridLayout* layout, 
				const int line,
				const int start_position
			);
	};
}
