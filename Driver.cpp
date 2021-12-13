#include "pch.h"
#include "Driver.h"

Loader::Loader()
{
	menu = 0;
	pmenu = key = -1;
	cam = new opencvCamera();
	ud = new UserData();
	cam->getInputCon();
}

void Loader::mainLoader()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "ASLearner");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				menu = 4;
			}
			else if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::Escape)
					menu = 4;
				else
					key = event.key.code;
			}
		}
		window.clear();

		switch (menu)
		{
		case 0:
			if (pmenu != menu) {
				menuScr = new menuScreen(menu, window, *cam, *ud);
				pmenu = 0;
			}
			menuScr->mainWindow(window);
			if (pmenu != 0) {
				delete menuScr;
				menuScr = NULL;
			}
			break;
		case 1:
			if (pmenu != menu) {
				tOne = new TeacherOne(menu, window, *cam, clock, *ud);
				pmenu = 1;
			}
			tOne->mainWindow(window, event);
			if (menu != 1) {
				delete tOne;
				tOne = NULL;
			}
			break;
		case 2:
			if (pmenu != menu) {
				ls = new levelSelect(menu, window, *cam, *ud);
				pmenu = 2;
			}
			ls->mainWindow(window);
			if (menu != 2) {
				delete ls;
				ls = NULL;
			}
			break;
		case 3:
			if (pmenu != menu) {
				ss = new ScoreScreen(menu, window, *cam, *ud);
				pmenu = 3;
			}
			ss->mainWindow(window);
			if (menu != 3) {
				delete ss;
				ss = NULL;
			}
			break;
		case 4:
			ud->~UserData();
			window.close();
			break;
		case 5:
			if (pmenu != menu) {
				lg = new LoginScreen(menu, window, *cam, *ud);
				pmenu = 5;
			}
			lg->mainWindow(window, key);
			if (menu != 5) {
				delete lg;
				lg = NULL;
			}
			break;
		default:
			break;
		}

		window.display();
	}
}

int main()
{
	//char pyFile[] = "Test.py";
	//FILE* fp;
	//PyObject* pInt;

	//Py_Initialize();

	//fp = _Py_fopen(pyFile, "r");
	//PyRun_SimpleFile(fp, pyFile);

	//Py_Finalize();

	Loader run;
	run.mainLoader();

	return 0;
}