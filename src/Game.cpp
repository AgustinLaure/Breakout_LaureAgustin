#include "Game.h"

namespace Game
{
	void game()
	{
		slWindow(Screen::height, Screen::width, Screen::windowName.c_str(), Screen::isFullScreen);

		while (!slShouldClose())
		{
			Screen::setBackColor(ColorInfo::ColorsName::RED);

			slRender();
		}


		slClose();
	}

	void init()
	{

	}
}