#include "keyboard.hpp"

using biv::KeyBoard;

KeyBoard::KeyBoard(const int width, QWidget* parent) 
	: button_width(width / 29), QWidget(parent) {

	// Загружаем данные раскладки, которые будут использованы при создании кнопок.
	keyboard_data = new KeyBoardData();
	
	// Grid layout позволяет задать разную ширину служебных клавиш.
    QGridLayout* keys_layout = new QGridLayout(this);
	keys_layout->setContentsMargins(0, 0, 0, 0);
    keys_layout->setSpacing(5);
	
	// Первый ряд: цифры и символы.
	create_buttons(keyboard_data->get_line1(), keys_layout, 0, 0);
	
	backspace_button = new KeyBoardButton("Удалить");
	backspace_button->setMinimumSize(2 * button_width, button_width);
	keys_layout->addWidget(backspace_button, 0, 26, 2, 3);
	connect(backspace_button, &QPushButton::clicked, this, &KeyBoard::backspace_pressed);

	// Второй ряд начинается с широкой клавиши Tab.
	KeyBoardButton* tab_btn = new KeyBoardButton("Tab");
	tab_btn->setMinimumSize(2 * button_width, button_width);
	keys_layout->addWidget(tab_btn, 2, 0, 2, 3);
	
	create_buttons(keyboard_data->get_line2(), keys_layout, 2, 3);
	
	// Третий ряд начинается с Caps и заканчивается Enter.
	KeyBoardButton* caps_btn = new KeyBoardButton("Caps");
	caps_btn->setMinimumSize(2 * button_width, button_width);
	keys_layout->addWidget(caps_btn, 4, 0, 2, 4);
	
	create_buttons(keyboard_data->get_line3(), keys_layout, 4, 4);
	
	enter_button = new KeyBoardButton("Enter");
	enter_button->setMinimumSize(2 * button_width, button_width);
	keys_layout->addWidget(enter_button, 4, 26, 2, 3);
	connect(enter_button, &QPushButton::clicked, this, &KeyBoard::enter_pressed);
	
	// Четвёртый ряд содержит две широкие клавиши Shift.
	KeyBoardButton* left_shift_btn = new KeyBoardButton("Shift");
	left_shift_btn->setMinimumSize(2 * button_width, button_width);
	keys_layout->addWidget(left_shift_btn, 6, 0, 2, 5);
	
	create_buttons(keyboard_data->get_line4(), keys_layout, 6, 5);
	
	KeyBoardButton* right_shift_btn = new KeyBoardButton("Shift");
	right_shift_btn->setMinimumSize(2 * button_width, button_width);
	keys_layout->addWidget(right_shift_btn, 6, 25, 2, 4);

	// Пятый ряд содержит пробел.
	space_button = new KeyBoardButton();
	space_button->setMinimumSize(8 * button_width, button_width);
	keys_layout->addWidget(space_button, 8, 7, 2, 16);
	connect(space_button, &QPushButton::clicked, this, [this]() {
		// Пробел передаётся тем же сигналом, что и обычные символьные клавиши.
		emit text_key_pressed(" ");
	});
}

void KeyBoard::animate_button(const int code) {
	// animateClick визуально подтверждает нажатие физической клавиши.
	buttons.at(code)->animateClick();
}

bool KeyBoard::animate_button_by_text(const QString& text) {
	// На macOS nativeVirtualKey не совпадает с кодами в таблице, поэтому используем текст события.
	const QString normalized_text = text.toUpper();
	for (const auto& button: buttons) {
		if (button.second->text() == normalized_text) {
			button.second->animateClick();
			return true;
		}
	}

	return false;
}

QString KeyBoard::get_key_text(const int code) const {
	// Текст виртуальной кнопки добавляется в поле вывода.
	return buttons.at(code)->text();
}

bool KeyBoard::is_key_allowed(const int code) const noexcept {
	// Решение о допустимости делегируется модели раскладки.
	return keyboard_data->is_key_allowed(code);
}

void KeyBoard::animate_backspace() {
	// animateClick запускает и визуальную анимацию, и общий обработчик кнопки.
	backspace_button->animateClick();
}

void KeyBoard::animate_enter() {
	// Enter обрабатывается через сигнал, поэтому мышь и физическая клавиша работают одинаково.
	enter_button->animateClick();
}

void KeyBoard::animate_space() {
	// Пробел также проходит через сигнал виртуальной кнопки.
	space_button->animateClick();
}

// ----------------------------------------------------------------------------
// 									PRIVATE
// ----------------------------------------------------------------------------
void KeyBoard::create_buttons(
	const std::vector<KeyData>& data, 
	QGridLayout* layout, 
	const int line,
	const int start_position
) {
	// Каждая клавиша занимает две строки и две условные колонки.
	for (int i = 0; i < data.size(); i++) {
        KeyBoardButton* btn = new KeyBoardButton(data[i].text);
		btn->setMinimumSize(button_width, button_width);
        
		layout->addWidget(btn, line, i * 2 + start_position, 2, 2);
		
		buttons[data[i].code] = btn;
		connect(btn, &QPushButton::clicked, this, [this, btn]() {
			// Клик по буквенной или цифровой кнопке передаёт её текст в окно.
			text_key_pressed(btn->text());
		});
	}
}
