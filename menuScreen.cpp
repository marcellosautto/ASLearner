#include "pch.h"
#include "menuScreen.h"

menuScreen::menuScreen(int& _menu, RenderWindow& _window, opencvCamera& _cam, UserData& _ud)
{
	menu = &_menu;
	window = &_window;
	cam = &_cam;
	ud = &_ud;

	sprites.CreateSprite("background", "Assets/MenuScreen/background.png");
	texts.createText("title", "Welcome To ASLearner!", "calibri", Color::Black, 100, 200, 50);
	buttons.push_back(new ButtonManager("Assets/Buttons/guest.png", 100, 850, 0.5f));
	buttons.push_back(new ButtonManager("Assets/Buttons/login.png", 700, 850, 0.5f));
	buttons.push_back(new ButtonManager("Assets/Buttons/exit.png", 1300, 850, 0.5f));
	
}

void menuScreen::mainWindow(RenderWindow& _window)
{
	sprites.DrawSprites(_window);

	if (buttons[0]->IsPressed())
		*menu = 2;
	else if (buttons[1]->IsPressed())
		*menu = 5;
	else if (buttons[2]->IsPressed()) 
		*menu = 4;
	
	for (short i = 0; i < buttons.size(); i++)
		buttons[i]->DrawButton(_window);

	texts.displayText(_window);

	cam->updateCamera(_window);
}