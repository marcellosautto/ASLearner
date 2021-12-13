#pragma once
#include "pch.h"
#include "SpriteManager.h"
#include "TextManager.h"
#include "ButtonManager.h"
#include "opencvCamera.h"
#include "UserData.h"

class ScoreScreen {
public:
	ScoreScreen(int& _menu, RenderWindow& _window, opencvCamera& _cam, UserData& _ud);
	void mainWindow(RenderWindow& _window);

private:

	int* menu, * assistance, * score, menuAssistance;
	RenderWindow* window;
	opencvCamera* cam = NULL;
	UserData* ud = NULL;

	SpriteManager sprites;
	TextManager texts;
	vector<ButtonManager*> buttons;

	char cLetter;
};