#pragma once 
#include "BaseObject.hpp"

namespace pav{
	class MovingItem : public BaseObject {
	public:
		MovingItem(const float xPos, const float yPos, 
		           const float oWidth, const float oHeight, 
		           const char inType)
			: BaseObject(xPos, yPos, oWidth, oHeight, inType) {}

		~MovingItem() override = default;

		void update(Game &game) override;
	};

}