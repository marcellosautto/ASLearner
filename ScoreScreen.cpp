#include "pch.h"
#include "ScoreScreen.h"

ScoreScreen::ScoreScreen(int& _menu, RenderWindow& _window, opencvCamera& _cam, UserData& _ud)
{
	menu = &_menu;
	window = &_window;
	cam = &_cam;
	ud = &_ud;

	assistance = ud->getAssistance();
	if (*assistance < 2)
		menuAssistance = 2;
	else
		menuAssistance = *assistance;

	score = ud->getScore();
	if(*score != 0)
		texts.createText("score", "Latest Score: " + to_string(*score) + "/26!", "calibri", sf::Color::Black, 40, 100, 20);
	sprites.CreateSprite("background", "Assets/TeacherOne/background.png");
	texts.createText("scoresUD", "Best Scores - " + ud->scoresToString(), "calibri", sf::Color::Black, 40, 100, 80);
	buttons.push_back(new ButtonManager("Assets/Buttons/logout.png", 700, 850, 0.5f));
	buttons.push_back(new ButtonManager("Assets/Buttons/Assistance.png", 100, 600, 0.5f, Color::Green, true));
	buttons.push_back(new ButtonManager("Assets/Buttons/exit.png", 1300, 850, 0.5f));
	buttons.push_back(new ButtonManager("Assets/Buttons/difficulty.png", 100, 850, 0.5f));
	buttons.push_back(new ButtonManager("Assets/Buttons/failed.png", 700, 600, 0.5f));

	if (*assistance == 0 || *assistance == 2)
		buttons[1]->Stick(true);
	
	else if (*assistance == 1 || *assistance == 3) 
		buttons[1]->Stick(false);
}

void ScoreScreen::mainWindow(RenderWindow& _window)
{
	sprites.DrawSprites(_window);

	if (buttons[0]->IsPressed())
		*menu = 0;
	else if (buttons[2]->IsPressed())
		*menu = 4;
	else if (buttons[3]->IsPressed())
		*menu = 2;
	else if (buttons[1]->IsPressed()) {
		if (*assistance == 2) {
			buttons[1]->Stick(false);
			*assistance = 3;
		}
		else if (*assistance == 3 || *assistance == 1 || *assistance == 0) {
			buttons[1]->Stick(true);
			*assistance = 2;
		}
		texts.editText("scoresUD", "Best Scores - " + ud->scoresToString());
	}
	else if (buttons[4]->IsPressed()) {
		*ud->getFailed() = true;
		if (*assistance == 2)
			*assistance = 0;
		else if (*assistance == 3)
			*assistance = 1;
		*menu = 1;
	}

	for (short i = 0; i < buttons.size() - 1; i++)
		buttons[i]->DrawButton(_window);
	if(*score != 26 && *score != 0 && ud->getRemainingLetters()->size() < 26)
		buttons[buttons.size() - 1]->DrawButton(_window);

	cam->updateCamera(_window);
	if(*score != 0)
		texts.displayText(_window, "score");
	texts.displayText(_window, "scoresUD");
}