#pragma once

#include <iostream>
#include "Color/Color.h"
#include "Math/Math.h"

namespace Screen
{
	const int intendedWidth = 1000;
	const int intendedHeight = 500;

	const std::string windowName = "Breakout";

	const bool isFullScreen = true;

	extern int width;
	extern int height;

	void setBackColor(Color::ColorsName colorName);
	void setForeColor(Color::ColorsName colorName, float opacity);
	void setForeDeaultColor();
	float getWidthRelativeValue(float nonRelativeValue);
	float getHeightRelativeValue(float nonRelativeValue);
	Math::Vector2 getPosRelativeValue(Math::Vector2 pos);
}

