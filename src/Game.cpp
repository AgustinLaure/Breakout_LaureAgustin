#include "Game.h"

namespace Game
{
	ColorInfo::ColorsName gameplayBackColor = ColorInfo::ColorsName::BLACK;

	void game()
	{
		slWindow(Screen::height, Screen::width, Screen::windowName.c_str(), Screen::isFullScreen);

		while (!slShouldClose())
		{
			float deltaTime = slGetDeltaTime();

			Paddle::Paddle paddle;

			Paddle::update(paddle, deltaTime);

			Screen::setBackColor(gameplayBackColor);
			Paddle::draw(paddle);

			slRender();
		}


		slClose();
	}

	void init()
	{

	}
}