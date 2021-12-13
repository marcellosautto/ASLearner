#include "pch.h"
#include "LevelSelect.h"

levelSelect::levelSelect(int& _menu, RenderWindow& _window, opencvCamera& _cam, UserData& _ud)
{
	ud = &_ud;
	menu = &_menu;
	window = &_window;
	cam = &_cam;
	assistance = ud->getAssistance();

	sprites.CreateSprite("background", "Assets/LevelSelect/background.png");
	texts.createText("title", "Select a Level", "calibri", Color::Black, 100, 200, 50);
	buttons.push_back(new ButtonManager("Assets/Buttons/start.png", 700, 300, 0.5f));
	buttons.push_back(new ButtonManager("Assets/Buttons/logout.png", 700, 850, 0.5f));
	buttons.push_back(new ButtonManager("Assets/Buttons/exit.png", 1300, 850, 0.5f));
	buttons.push_back(new ButtonManager("Assets/Buttons/Assistance.png", 100, 300, 0.5f, Color::Green, true));
	buttons.push_back(new ButtonManager("Assets/Buttons/Test.png", 100, 600, 0.5f, Color::Green, false));
	buttons.push_back(new ButtonManager("Assets/Buttons/HighScores.png", 100, 850, 0.5f));
	buttons.push_back(new ButtonManager("Assets/Buttons/failed.png", 700, 600, 0.5f));

	if (*assistance == 1) {
		buttons[3]->Stick(false);
		buttons[4]->Stick(false);
	}
	else if (*assistance == 3) {
		buttons[3]->Stick(false);
		buttons[4]->Stick(true);
	}
	else if (*assistance == 2) {
		buttons[3]->Stick(true);
		buttons[4]->Stick(true);
	}
}

void levelSelect::mainWindow(RenderWindow& _window)
{
	sprites.DrawSprites(_window);

	if (buttons[0]->IsPressed()) {
		*ud->getFailed() = false;
		*menu = 1;
	}
	else if (buttons[1]->IsPressed()) {
		ud->login("");
		*menu = 0;
	}
	else if (buttons[6]->IsPressed()) {
		*ud->getFailed() = true;
		if (*assistance == 2)
			*assistance = 0;
		else if (*assistance == 3)
			*assistance = 1;
		*menu = 1;
	}
	else if (buttons[5]->IsPressed()) {
		*menu = 3;
	}
	else if (buttons[2]->IsPressed())
		*menu = 4;
	else if (buttons[3]->IsPressed()) {
		if (*assistance == 0) {
			buttons[3]->Stick(false);
			*assistance = 1;
		}
		else if (*assistance == 1) {
			buttons[3]->Stick(true);
			*assistance = 0;
		}
		else if (*assistance == 2) {
			buttons[3]->Stick(false);
			*assistance = 3;
		}
		else if (*assistance == 3) {
			buttons[3]->Stick(true);
			*assistance = 2;
		}
	}
	else if (buttons[4]->IsPressed()) {
		if (*assistance == 0) {
			buttons[4]->Stick(true);
			*assistance = 2;
		}
		else if (*assistance == 2) {
			buttons[4]->Stick(false);
			*assistance = 0;
		}
		else if (*assistance == 1) {
			buttons[4]->Stick(true);
			*assistance = 3;
		}
		else if (*assistance == 3) {
			buttons[4]->Stick(false);
			*assistance = 1;
		}
	}
	for (short i = 0; i < buttons.size() - 1; i++)
		buttons[i]->DrawButton(_window);

	if (*ud->getFailed() && ud->getRemainingLetters()->size() < 26)
		buttons[buttons.size() - 1]->DrawButton(_window);
	texts.displayText(_window);

	cam->updateCamera(_window);
}