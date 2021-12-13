#pragma once
#include "pch.h"
#include "menuScreen.h"
#include "opencvCamera.h"
#include "TeacherOne.h"
#include "LevelSelect.h"
#include "ScoreScreen.h"
#include "LoginScreen.h"
#include "UserData.h"

class Loader {
public:
	void mainLoader();

	Loader();

private:
	int menu, pmenu, key;
	string username;
	menuScreen* menuScr = NULL;
	TeacherOne* tOne = NULL;
	opencvCamera* cam = NULL;
	levelSelect* ls = NULL;
	ScoreScreen* ss = NULL;
	LoginScreen* lg = NULL;
	UserData* ud = NULL;
	Clock clock;
};