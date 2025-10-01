#pragma once

namespace Color
{
	enum class ColorsName
	{
		RED,
		GREEN,
		BLUE,
		WHITE,
		BLACK,
		YELLOW,
		LIGHTBLUE,
		VIOLET
	};

	struct Rgba
	{
		double r = 0;
		double g = 0;
		double b = 0;
		double a = 0;
	};

	const int maxColors = 8;
	const Rgba standardColor = { 1.0, 1.0, 1.0, 1.0 };

	const Rgba colorsName[maxColors] =
	{
		{1.0, 0.0, 0.0, 1.0},
		{0.0, 1.0, 0.0, 1.0},
		{0.0, 0.0, 1.0, 1.0},
		{1.0, 1.0, 1.0, 1.0},
		{0.0, 0.0, 0.0, 1.0},
		{1.0, 1.0, 0.0, 1.0},
		{0.0, 0.97,1.0,1.0},
		{0.67,0.0,1.0,1.0}
	};

	Color::Rgba getColor(Color::ColorsName color);
}
