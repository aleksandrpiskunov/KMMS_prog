#pragma once

#include <vector>

#include "key_data.hpp"

namespace biv {
	// Хранит раскладку клавиатуры и проверяет допустимость кодов клавиш.
	class KeyBoardData {
		private:
			// Общий список клавиш используется для построения четырёх рядов.
			static const std::vector<KeyData> KEYS;

		public:
			// Возвращают данные отдельных рядов виртуальной клавиатуры.
			std::vector<KeyData> get_line1() const;
			std::vector<KeyData> get_line2() const;
			std::vector<KeyData> get_line3() const;
			std::vector<KeyData> get_line4() const;
			
			// Проверяет, можно ли отобразить на клавиатуре переданный код.
			bool is_key_allowed(const int code) const noexcept;
	};
}
