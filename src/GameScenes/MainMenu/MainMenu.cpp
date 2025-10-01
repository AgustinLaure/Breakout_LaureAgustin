#include <vector>
#include "sl.h"
#include "GameScenes/MainMenu/MainMenu.h"
#include "Screen/Screen.h"
#include "Button/Button.h"
#include "Player/Player.h"

namespace MainMenu
{
	Math::Vector2 titlePos =
	{
		Screen::getPosRelativeValue({titleIntendedPos.x,titleIntendedPos.y })
	};
	float titleFontSize = Screen::getHeightRelativeValue(titleIntendedFontSize);
		
	Math::Vector2 creditsPos =
	{
		Screen::getPosRelativeValue({creditsIntendedPos.x,creditsIntendedPos.y})
	};
	float creditsFontSize = Screen::getHeightRelativeValue(creditsIntendedFontSize);
	float creditsDistance = Screen::getHeightRelativeValue(creditsIntendedDistance);

	Math::Vector2 rulesPos =
	{
		Screen::getPosRelativeValue({rulesIntendedPos.x,rulesIntendedPos.y})
	};
	float rulesFontSize = Screen::getHeightRelativeValue(rulesIntendedFontSize);
	float rulesDistanceBetweenLines = Screen::getHeightRelativeValue(intendedRulesDistanceBetweenLines);

	void mainMenu(MainMenuButton mainMenuButtons[buttonsSize], MainMenuButton& backButton, Text::Text title, Text::Text credits[],	Text::Text rules[], GameScenes::GameScenes& currentScene, MainMenuScenes& currentMainMenuScene, Player::Input inputs[])
	{
		switch (currentMainMenuScene)
		{
		case MainMenu::MainMenuScenes::Menu:
			mainMenuUpdate(mainMenuButtons, currentScene, currentMainMenuScene, inputs);
			drawText(title);
			drawAllButtons(mainMenuButtons);
			break;

		case MainMenu::MainMenuScenes::Rules:
			rulesUpdate(backButton, currentMainMenuScene, inputs);
			drawButton(backButton);
			drawRules(rules);
			break;
		case MainMenu::MainMenuScenes::Credits:
			creditsUpdate(backButton, currentMainMenuScene, inputs);
			drawButton(backButton);
			drawCredits(credits);
			break;
		default:
			break;
		}
	}

	void mainMenuUpdate(MainMenuButton mainMenuButtons[buttonsSize], GameScenes::GameScenes& currentScene, MainMenuScenes& currentMainMenuScene, Player::Input inputs[])
	{
		for (int button = 0; button < buttonsSize; button++)
		{
			MainMenuButtonIntended intendedButton = intendedButtons[int(button)];

			mainMenuButtons[button].button.isPressed = false;
			mainMenuButtons[button].button.text.opacity = intendedButton.opacity;

			if (Forms::isInsideRectangle({ float(slGetMouseX()), float(slGetMouseY()) }, mainMenuButtons[button].button.area))
			{
				mainMenuButtons[button].button.text.opacity = intendedButton.opacity - Button::onHoverOpacity;

				if (inputs[int(Player::PossibleKeys::LeftClick)].eventIsHold)
				{
					mainMenuButtons[button].button.text.opacity = intendedButton.opacity - Button::onSelectOpacity;
				}
				if (inputs[int(Player::PossibleKeys::LeftClick)].eventIsJustReleased &&
					inputs[int(Player::PossibleKeys::LeftClick)].isValid)
				{
					currentScene = mainMenuButtons[button].pointingGameScene;
					currentMainMenuScene = mainMenuButtons[button].pointingMainMenuScene;
					inputs[int(Player::PossibleKeys::LeftClick)].isValid = false;
				}

				if (inputs[int(Player::PossibleKeys::LeftClick)].eventIsUp)
				{
					inputs[int(Player::PossibleKeys::LeftClick)].isValid = true;
				}
			}
		}
	}

	void rulesUpdate(MainMenuButton& backButton, MainMenuScenes& currentMainMenuScene, Player::Input inputs[])
	{
		backButton.button.isPressed = false;
		backButton.button.text.opacity = backButtonIntended.opacity;

		if (Forms::isInsideRectangle({ float(slGetMouseX()), float(slGetMouseY()) }, backButton.button.area))
		{
			backButton.button.text.opacity -= Button::onHoverOpacity;
			if (slGetMouseButton(Player::optionSelect))
			{
				currentMainMenuScene = backButtonIntended.pointingMainMenuScene;
			}
		}
	}

	void creditsUpdate(MainMenuButton& backButton, MainMenuScenes& currentMainMenuScene, Player::Input inputs[])
	{
		backButton.button.isPressed = false;
		backButton.button.text.opacity = backButtonIntended.opacity;

		if (Forms::isInsideRectangle({ float(slGetMouseX()), float(slGetMouseY()) }, backButton.button.area))
		{
			backButton.button.text.opacity -= Button::onHoverOpacity;
			if (slGetMouseButton(Player::optionSelect))
			{
				currentMainMenuScene = backButtonIntended.pointingMainMenuScene;
			}
		}
	}

	void drawButton(MainMenuButton mainMenuButton)
	{
		drawText(mainMenuButton.button.text);
	}

	void drawAllButtons(MainMenuButton mainMenuButtons[buttonsSize])
	{
		for (int button = 0; button < buttonsSize; button++)
		{
			drawButton(mainMenuButtons[button]);
		}
	}

	void initMainMenuButton(MainMenuButton& mainMenuButton, MainMenuButtonIntended intendedButton)
	{
		mainMenuButton.button.text.position =
		{
			Screen::getWidthRelativeValue(intendedButton.pos.x),
			Screen::getHeightRelativeValue(intendedButton.pos.y)
		};

		mainMenuButton.button.text.fontId = slLoadFont(intendedButton.fontName.c_str());
		mainMenuButton.button.text.fontSize = Screen::getWidthRelativeValue(intendedButton.fontSize);
		mainMenuButton.button.text.text = intendedButton.text;
		mainMenuButton.button.text.color = intendedButton.color;
		mainMenuButton.button.text.opacity = intendedButton.opacity;
		slSetFont(mainMenuButton.button.text.fontId, mainMenuButton.button.text.fontSize);
		mainMenuButton.button.area.width = slGetTextWidth(mainMenuButton.button.text.text.c_str());
		mainMenuButton.button.area.height = slGetTextHeight(mainMenuButton.button.text.text.c_str());
		mainMenuButton.button.area.position = { mainMenuButton.button.text.position.x, mainMenuButton.button.text.position.y + mainMenuButton.button.area.height };
		mainMenuButton.button.isPressed = false;
		mainMenuButton.pointingGameScene = intendedButton.pointingGameScene;
		mainMenuButton.pointingMainMenuScene = intendedButton.pointingMainMenuScene;
	}

	void drawRules(Text::Text rules[])
	{
		for (int i = 0; i < maxRulesLines; i++)
		{
			drawText(rules[i]);
		}
	}

	void drawCredits(Text::Text credits[])
	{
		for (int i = 0; i < maxCreditsLines; i++)
		{
			drawText(credits[i]);
		}
	}
}
