#include "Game.h"

namespace Game
{
	ColorInfo::ColorsName gameplayBackColor = ColorInfo::ColorsName::BLACK;

	void game()
	{
		slWindow(Screen::height, Screen::width, Screen::windowName.c_str(), Screen::isFullScreen);

		while (!slShouldClose())
		{
			Screen::setBackColor(gameplayBackColor);

			slRender();
		}


		slClose();
	}

	void init()
	{

	}
}