#pragma once
#include <iostream>
#include "Color/Color.h"
#include "Math/Math.h"

namespace Text
{
	struct Text
	{
		Math::Vector2 position = {};
		int fontId = 0;
		int fontSize = 0;
		std::string text = " ";
		Color::ColorsName color = Color::ColorsName::WHITE;
		float opacity = 1.0f;
	};

	struct TextIntended
	{
		Math::Vector2 intendedPos = {};
		int intendedFontSize = 1;
		std::string text = " ";
		std::string fontName = " ";
		Color::ColorsName baseColor = Color::ColorsName::WHITE;
		float initialOpacity = 1.0f;
	};

	void drawText(Text text);
	void initText(Text& text, Math::Vector2 pos, std::string fontName, float fontSize, std::string message, Color::ColorsName baseColor, float opacity);
}

