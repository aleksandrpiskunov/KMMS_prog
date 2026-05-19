#pragma once 
#include "BaseClass.hpp"

namespace pav{
	class Mario : public TObject {
	public:
        Mario(const float xPos, const float yPos, 
                   const float oWidth, const float oHeight, 
                   const char inType)
            : TObject(xPos, yPos, oWidth, oHeight, inType) {}

        ~Mario() override = default;
        void mario_collision(Game &game);
        void player_dead(Game &game);

        void update(Game &game) override;
	};

}