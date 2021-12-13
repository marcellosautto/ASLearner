#pragma once
#include "pch.h"
#include "SpriteManager.h"
#include "TextManager.h"
#include "ButtonManager.h"
#include "opencvCamera.h"
#include "UserData.h"

using namespace sf;

class LoginScreen {
public:
	LoginScreen(int& _menu, RenderWindow& _window, opencvCamera& _cam, UserData& _ud);
	void mainWindow(RenderWindow& _window, int& _key);

private:
	int* menu;
	bool loggedin;
	string tempUsername;
	RenderWindow* window;
	opencvCamera* cam = NULL;
	UserData* ud = NULL;

	SpriteManager sprites;
	TextManager texts;
	vector<ButtonManager*> buttons;

	void login(int& _key);
};