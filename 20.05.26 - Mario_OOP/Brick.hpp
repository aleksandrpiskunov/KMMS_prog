#pragma once 
#include "TObject.hpp"

namespace pav{
	class Brick : public TObject {
	public:
        Brick(const float xPos, const float yPos, 
                   const float oWidth, const float oHeight, 
                   const char inType)
            : TObject(xPos, yPos, oWidth, oHeight, inType) {}

                ~Brick() override = default;

                void update(Game &game) override {
                        // static block — nothing to do each frame
                }
	};

}