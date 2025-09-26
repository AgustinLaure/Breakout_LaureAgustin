#pragma once
#include <iostream>

namespace screen
{
	const int width = 1080;
	const int height = 720;

	const std::string windowName = "Breakout";
	const bool isFullScreen = false;


}

enum class colorsName
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

const Rgba colors[maxColors] =
{
	
	{1.0, 0.0, 0.0, 1.0}, 
	{0.0, 1.0, 0.0, 1.0},
	{0.0, 0.0, 1.0, 1.0},
	
		
};

