#include "sl.h"
#include "Screen/Screen.h"

namespace Screen
{
	int width = 1920;
	int height = 1080;

	void setBackColor(Color::ColorsName colorName)
	{
		Color::Rgba color = Color::getColor(colorName);
		slSetBackColor(color.r, color.g, color.b);
	}

	void setForeColor(Color::ColorsName colorName, float opacity)
	{
		Color::Rgba color = Color::getColor(colorName);
		slSetForeColor(color.r, color.g, color.b, opacity);
	}

	void setForeDeaultColor()
	{
		slSetForeColor(Color::standardColor.r, Color::standardColor.g, Color::standardColor.b, Color::standardColor.a);
	}

	float getWidthRelativeValue(float nonRelativeValue)
	{
		float trueValue = 0.0f;

		trueValue = Screen::width* nonRelativeValue / Screen::intendedWidth;

		return trueValue;
	}

	float getHeightRelativeValue(float nonRelativeValue)
	{
		float trueValue = 0.0f;

		trueValue = Screen::height* nonRelativeValue / Screen::intendedHeight;

		return trueValue;
	}

	Math::Vector2 getPosRelativeValue(Math::Vector2 pos)
	{
		Math::Vector2 relativePos = {};

		relativePos.x = getWidthRelativeValue(pos.x);
		relativePos.y = getHeightRelativeValue(pos.y);

		return relativePos;
	}
}