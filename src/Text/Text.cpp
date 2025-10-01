#include "sl.h"
#include "Text/Text.h"
#include "Screen/Screen.h"

namespace Text
{
	void drawText(Text text)
	{
		Screen::setForeColor(text.color, text.opacity);

		slSetFont(text.fontId, text.fontSize);
		text.position.x -= slGetTextWidth(text.text.c_str()) / 2;
		slSetFontSize(text.fontSize);
		slText(text.position.x, text.position.y, text.text.c_str());

		Screen::setForeDeaultColor();
	}

	void initText(Text& text, Math::Vector2 pos, std::string fontName, float fontSize, std::string message, Color::ColorsName baseColor, float opacity)
	{
		text.position = pos;
		text.fontId = slLoadFont(fontName.c_str());
		text.fontSize = fontSize;
		text.text = message;
		text.color = baseColor;
		text.opacity = opacity;
	}
}
