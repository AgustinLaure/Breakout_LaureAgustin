#include "Game.h"

void game()
{
	slWindow(Screen::height, Screen::width, Screen::windowName.c_str(), Screen::isFullScreen);

	while (!slShouldClose())
	{


		Screen::setBackColor(Screen::ColorsName::RED);


		// smaller subtext
		slSetFontSize(14);
		slText(200, 220, "Sprites, text, sound, input, and more!");
		slLine(48, 210, 352, 210);

		slRender();
	}


	slClose();
}

void init()
{

}