#pragma once

#include <iostream>
#include "sl.h"
#include "Color.h"

namespace Screen
{
	const int width = 1080;
	const int height = 720;

	const std::string windowName = "Breakout";
	const bool isFullScreen = false;

	ColorInfo::Rgba getColor(ColorInfo::ColorsName color);
	void setBackColor(ColorInfo::ColorsName colorName);

}

