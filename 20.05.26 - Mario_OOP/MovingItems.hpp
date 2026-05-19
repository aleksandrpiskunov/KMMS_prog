#pragma once 
#include "TObject.hpp"

namespace pav{
	class MovingItem : public TObject {
	public:
        MovingItem(const float xPos, const float yPos, 
                   const float oWidth, const float oHeight, 
                   const char inType)
            : TObject(xPos, yPos, oWidth, oHeight, inType) {}

        ~MovingItem() override = default;

        void update(Game &game) override;
	};

}