#pragma once

namespace ColorInfo
{
	enum class ColorsName
	{
		RED,
		GREEN,
		BLUE,
		WHITE,
		BLACK
	};

	struct Rgba
	{
		double r = 0;
		double g = 0;
		double b = 0;
		double a = 0;
	};

	const int maxColors = 5;

	const Rgba ColorsName[maxColors] =
	{

		{1.0, 0.0, 0.0, 1.0},
		{0.0, 1.0, 0.0, 1.0},
		{0.0, 0.0, 1.0, 1.0},

	};
}
