#pragma once

#include "game_level.hpp"

namespace biv {
	class FirstLevel : public GameLevel {
		public:
			FirstLevel(UIFactory* ui_factory);
			
			GameLevel* get_next() override;
			
		private:
			void init_data() override;
	};
}
