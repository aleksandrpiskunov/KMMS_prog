#include "TObject.hpp"

using pav::TObject;

TObject::TObject(const float xPos, const float yPos, const float oWidth, const float oHeight, const char inType)
	: x(xPos), y(yPos), width(oWidth), height(oHeight), vertSpeed(0.0f), IsFly(false), cType(inType), horizSpeed(0.0f)
{
}

