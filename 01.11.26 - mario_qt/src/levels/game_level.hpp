#pragma once

/**
	- На какую структуру данных похож класс GameLevel?
	- В чём это выражается?
	- Можно ли создавать экземпляры класса GameLevel и почему?
	- В чём + и - конструкции GameLevel?
*/

#include <cstddef>

#include "ui_factory.hpp"

namespace biv {
	class GameLevel {
		protected:
			UIFactory* ui_factory = nullptr;
			
			GameLevel* parent = nullptr;
			GameLevel* next = nullptr;

		protected:
			GameLevel(UIFactory*);

		public:
			virtual void restart();
			virtual bool is_final() const noexcept;

			virtual GameLevel* get_next() = 0;

		protected:
			void clear_data();

			virtual void init_data() = 0;
	};
}
