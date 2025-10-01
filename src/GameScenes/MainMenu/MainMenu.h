#pragma once
#include <iostream>
#include "Button/Button.h"
#include "Screen/Screen.h"
#include "GameScenes/GameScenes.h"
#include "Player/Player.h"

using namespace std;

namespace MainMenu
{
	static const Math::Vector2 titleIntendedPos = { 500, 365 };
	static const int titleIntendedFontSize = 45;
	static const string titleText = "BREAKOUT";
	static const string titleFontName = "res/ARCADE_I.TTF";
	const Color::ColorsName titleBaseColor = Color::ColorsName::RED;
	const float titleInitialOpacity = 1.0f;

	extern Math::Vector2 titlePos;
	extern float titleFontSize;

	const int maxCreditsLines = 1;
	static Math::Vector2 creditsIntendedPos = {Screen::intendedWidth / 2, Screen::intendedHeight / 2};
	static const int creditsIntendedFontSize = 25;
	static const string creditsText = "Game created by Agustin Laure";
	static const string creditsFontName = "res/ARCADE_I.TTF";
	const Color::ColorsName creditsBaseColor = Color::ColorsName::WHITE;
	const float creditsInitialOpacity = 1.0f;

	extern Math::Vector2 creditsPos;
	extern float creditsFontSize;

	const int maxRulesLines = 3;
	const float intendedRulesDistanceBetweenLines = 100.0f;
	static Math::Vector2 rulesIntendedPos = { Screen::intendedWidth / 2, Screen::intendedHeight - 120 };
	static const int rulesIntendedFontSize = 15;
	static const string rulesText1 = "Destroy all the blocks by hitting them with the ball";
	static const string rulesText2 = "Use <-  and  -> to move left and right";
	static const string rulesText3 = "(ESC) to pause and (TAB) to shoot the ball";
	static const string rulesFontName = "res/ARCADE_I.TTF";
	const Color::ColorsName rulesBaseColor = Color::ColorsName::WHITE;
	const float rulesInitialOpacity = 1.0f;

	extern Math::Vector2 rulesPos;
	extern float rulesFontSize;
	extern float rulesDistanceBetweenLines;

	enum class MainMenuScenes
	{
		None,
		Menu,
		Rules,
		Credits,
	};

	struct MainMenuButtonIntended
	{
		Math::Vector2 pos = {};
		string fontName = " ";
		int fontSize = 0;
		string text = " ";
		Color::ColorsName color = Color::ColorsName::WHITE;
		float opacity = 1.0f;
		GameScenes::GameScenes pointingGameScene;
		MainMenuScenes pointingMainMenuScene;
	};

	enum class MainMenuButtons
	{
		Play,
		Rules,
	};

	struct MainMenuButton
	{
		Button::Button button;
		GameScenes::GameScenes pointingGameScene;
		MainMenuScenes pointingMainMenuScene;
	};

	const int buttonsSize = 4;

	const MainMenuButtonIntended intendedButtons[buttonsSize] =
	{
		//NewButton
		{
			{Screen::intendedWidth / 5,100}		//Pos
			,"res/ARCADE_I.TTF"					//FontName
			,22									//FontSize
			,"PLAY"								//Text
			,Color::ColorsName::WHITE			//Color
			,1.0f								//Opacity
			,GameScenes::GameScenes::Gameplay	//PointingGameScene
			,MainMenuScenes::Menu				//PointingMainMenuScene
		},

		//NewButton
		{
			{Screen::intendedWidth / 5 * 2,100}
			,"res/ARCADE_I.TTF"
			,22
			,"RULES"
			,Color::ColorsName::WHITE
			,1.0f
			,GameScenes::GameScenes::MainMenu
			,MainMenuScenes::Rules
		},

		//NewButton
		{
			{Screen::intendedWidth / 5 * 3,100}
			,"res/ARCADE_I.TTF"
			,22
			,"CREDITS"
			,Color::ColorsName::WHITE
			,1.0f
			,GameScenes::GameScenes::MainMenu
			,MainMenuScenes::Credits
		},

		//NewButton
		{
			{Screen::intendedWidth / 5 * 4,100}
			,"res/ARCADE_I.TTF"
			,22
			,"EXIT"
			,Color::ColorsName::WHITE
			,1.0f
			,GameScenes::GameScenes::Exit
			,MainMenuScenes::Menu
		},
	};

	const MainMenuButtonIntended backButtonIntended =
	{
			{Screen::intendedWidth / 5,50}		//Pos
			,"res/ARCADE_I.TTF"					//FontName
			,22									//FontSize
			,"BACK"								//Text
			,Color::ColorsName::WHITE			//Color
			,1.0f								//Opacity
			,GameScenes::GameScenes::MainMenu	//PointingGameScene
			,MainMenuScenes::Menu				//PointingMainMenuScene
	};

	void mainMenu(MainMenuButton mainMenuButtons[buttonsSize], MainMenuButton& backButton, Text::Text title, Text::Text credits[], Text::Text rules[], GameScenes::GameScenes& currentScene, MainMenuScenes& currentMainMenuScene, Player::Input inputs[]);
	void mainMenuUpdate(MainMenuButton mainMenuButtons[buttonsSize], GameScenes::GameScenes& currentScene, MainMenuScenes& currentMainMenuScene, Player::Input inputs[]);
	void rulesUpdate(MainMenuButton& backButton, MainMenuScenes& currentMainMenuScene, Player::Input inputs[]);
	void creditsUpdate(MainMenuButton& backButton, MainMenuScenes& currentMainMenuScene, Player::Input inputs[]);
	void drawButton(MainMenuButton button);
	void drawAllButtons(MainMenuButton mainMenuButtons[buttonsSize]);
	void initMainMenuButton(MainMenuButton& mainMenuButton, MainMenuButtonIntended intendedButton);
	void drawRules(Text::Text rules[]);
	void drawCredits(Text::Text credits[]);
}

