#pragma once

#include <iostream>
#include "sl.h"
#include "Color.h"

namespace Screen
{
	const std::string windowName = "Breakout";

	const bool isFullScreen = false;

	extern int width;
	extern int height;

	ColorInfo::Rgba getColor(ColorInfo::ColorsName color);
	void setBackColor(ColorInfo::ColorsName colorName);
}

