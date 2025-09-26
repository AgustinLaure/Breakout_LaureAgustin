#include "Game.h"

namespace Game
{
	ColorInfo::ColorsName gameplayBackColor = ColorInfo::ColorsName::BLACK;

	void game()
	{
		slWindow(Screen::height, Screen::width, Screen::windowName.c_str(), Screen::isFullScreen);

		Paddle::Paddle paddle;

		while (!slShouldClose())
		{
			float deltaTime = slGetDeltaTime();

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