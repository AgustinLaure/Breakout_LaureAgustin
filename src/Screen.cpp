#include "Screen.h"

namespace Screen
{
	int width = 1080;
	int height = 720;

	ColorInfo::Rgba getColor(ColorInfo::ColorsName color)
	{
		return ColorInfo::colorsName[int(color)];
	}

	void setBackColor(ColorInfo::ColorsName colorName)
	{
		ColorInfo::Rgba color = getColor(colorName);
		slSetBackColor(color.r, color.g, color.b);
	}
}