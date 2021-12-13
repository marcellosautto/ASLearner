#pragma once
#include "pch.h"
#include "SpriteManager.h"
#include "TextManager.h"
#include "ButtonManager.h"
#include "opencvCamera.h"
#include "UserData.h"

class TeacherOne {
public:
	TeacherOne(int& _menu, RenderWindow& _window, opencvCamera& _cam, Clock& _clock, UserData& _ud);
	~TeacherOne();
	void mainWindow(RenderWindow& _window, Event _event);

private:
	int* menu, * assistance, * score;
	bool* fail;
	RenderWindow* window;
	opencvCamera* cam = NULL;
	UserData* ud = NULL;
	Clock* clock;
	Time correctTimer, incorrectTimer, testCountDown, aniTimer;
	vector<char>* failedLetters, * remainingLetters;

	SpriteManager sprites, lettersSprites;
	TextManager texts;
	vector<ButtonManager*> buttons;

	void pollInput(Event _event, char _letter);
};