#include "pch.h"
#include "LoginScreen.h"

LoginScreen::LoginScreen(int& _menu, RenderWindow& _window, opencvCamera& _cam, UserData& _ud)
{
	menu = &_menu;
	window = &_window;
	cam = &_cam;
	ud = &_ud;
	loggedin = false;

	sprites.CreateSprite("background", "Assets/LevelSelect/background.png");
	texts.createText("title", "Use Keyboard to Create or Login to an Account", "calibri", Color::Black, 90, 100, 50);
	buttons.push_back(new ButtonManager("Assets/Buttons/MainMenu.png", 700, 850, 0.5f));
	buttons.push_back(new ButtonManager("Assets/Buttons/exit.png", 1300, 850, 0.5f));
	buttons.push_back(new ButtonManager("Assets/Buttons/login.png", 100, 850, 0.5f));
	buttons.push_back(new ButtonManager("Assets/Buttons/difficulty.png", 700, 600, 0.5f));
	buttons.push_back(new ButtonManager("Assets/Buttons/HighScores.png", 100, 600, 0.5f));

	texts.createText("username", "Enter Username: \n", "calibri", Color::Black, 90, 100, 300);
}

void LoginScreen::mainWindow(RenderWindow& _window, int& _key)
{
	login(_key);

	sprites.DrawSprites(_window);

	if (buttons[0]->IsPressed())
		*menu = 0;
	if (buttons[1]->IsPressed())
		*menu = 4;
	if (buttons[2]->IsPressed()) {
		if (tempUsername == "")
			texts.editText("username", "Invalid Username!");
		else {
			if (ud->login(tempUsername))
				texts.editText("username", "Account Created: \n" + tempUsername);
			else
				texts.editText("username", "Logged In: \n" + tempUsername);
			loggedin = true;
		}
	}
	if (buttons[3]->IsPressed())
		*menu = 2;
	if (buttons[4]->IsPressed())
		*menu = 3;

	for (short i = 0; i < buttons.size() - 2; i++)
		buttons[i]->DrawButton(_window);
	if (loggedin) {
		buttons[buttons.size() - 1]->DrawButton(_window);
		buttons[buttons.size() - 2]->DrawButton(_window);
	}

	texts.displayText(_window);

	cam->updateCamera(_window);
}

void LoginScreen::login(int& _key)
{
	if (_key >= 0 && _key < 26) {
		tempUsername.push_back(char(_key + 97));
		texts.editText("username", "Enter Username: \n" + tempUsername);
	}
	else if (_key == 59 && tempUsername.size() != 0) {
		tempUsername.pop_back();
		texts.editText("username", "Enter Username: \n" + tempUsername);
	}
	_key = -1;
}