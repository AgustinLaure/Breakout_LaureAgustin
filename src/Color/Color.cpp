#include "Color/Color.h"

namespace Color
{
	Color::Rgba getColor(Color::ColorsName color)
	{
		return Color::colorsName[int(color)];
	}
}