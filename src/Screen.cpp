#include "Screen.h"

namespace Screen
{
	ColorInfo::Rgba getColor(ColorInfo::ColorsName color)
	{
		return ColorInfo::ColorsName[int(color)];
	}

	void setBackColor(ColorInfo::ColorsName colorName)
	{
		ColorInfo::Rgba color = Screen::getColor(colorName);
		slSetBackColor(color.r, color.g, color.b);
	}
}