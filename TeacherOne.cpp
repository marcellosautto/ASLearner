#include "pch.h"
#include "TeacherOne.h"

TeacherOne::TeacherOne(int& _menu, RenderWindow& _window, opencvCamera& _cam, Clock& _clock, UserData& _ud)
{
	menu = &_menu;
	window = &_window;
	cam = &_cam;
	clock = &_clock;
	ud = &_ud;
	assistance = ud->getAssistance();
	score = ud->getScore();
	fail = ud->getFailed();
	if (!*fail)
		if (*assistance > 1)
			ud->genRemainingLetters(true);
		else
			ud->genRemainingLetters(false);
	else {
		ud->genFailLetters();
		*fail = false;
	}

	remainingLetters = ud->getRemainingLetters();
	failedLetters = ud->getFailedLetters();

	*score = 0;

	sprites.CreateSprite("background", "Assets/TeacherOne/background.png");
	buttons.push_back(new ButtonManager("Assets/Buttons/difficulty.png", 100, 850, 0.5f));
	buttons.push_back(new ButtonManager("Assets/Buttons/exit.png", 1300, 850, 0.5f));
	if (*assistance == 0 || *assistance == 2)
		lettersSprites.CreateSprites("Assets/TeacherOne/AssistanceLetters", { 1.4, 1.4 }, { 1000, 800 });
	else
		lettersSprites.CreateSprites("Assets/TeacherOne/Letters", { 1.4, 1.4 }, { 1000, 800 });

	texts.createText("correct", "Correct!", "calibri", sf::Color::Green, 150, 650, 850);
	texts.createText("incorrect", "Incorrect!", "calibri", sf::Color::Red, 150, 650, 850);
	texts.createText("time", "0", "calibri", sf::Color::Black, 100, 1000, 25);
	texts.createText("score", "Score: 0/26", "calibri", sf::Color::Black, 100, 1375, 125);
	texts.createText("letter", "a", "calibri", sf::Color::Red, 100, 1650, 735);

	testCountDown = sf::seconds(6.0f) + clock->getElapsedTime();
	aniTimer = sf::seconds(0.f);
}

TeacherOne::~TeacherOne()
{
	if (remainingLetters->size() > 0 || failedLetters->size() > 0)
		*ud->getFailed() = true;
	else if (remainingLetters->size() > 25 || failedLetters->size() > 25) {
		remainingLetters->clear();
		failedLetters->clear();
	}
	else
		*ud->getFailed() = false;
}

void TeacherOne::mainWindow(RenderWindow& _window, Event _event)
{
	char letter = cam->getInput();
	pollInput(_event, letter);

	sprites.DrawSprites(_window);

	if (buttons[0]->IsPressed())
		*menu = 2;
	if (buttons[1]->IsPressed())
		*menu = 4;

	for (short i = 0; i < buttons.size(); i++)
		buttons[i]->DrawButton(_window);

	cam->updateCamera(_window);

	_window.draw(lettersSprites.GetSprite(string(1, remainingLetters->at(remainingLetters->size() - 1))));

	if (correctTimer > clock->getElapsedTime())
		texts.displayText(_window, "correct");

	if (incorrectTimer > clock->getElapsedTime())
		texts.displayText(_window, "incorrect");

	if (*assistance == 2 || *assistance == 3) {
		texts.editText("time", "Seconds Remaining: " + to_string(int(testCountDown.asSeconds() - clock->getElapsedTime().asSeconds())));
		texts.displayText(_window, "time");
		texts.displayText(_window, "score");
	}

	if (int(aniTimer.asMilliseconds() - clock->getElapsedTime().asMilliseconds()) < 0) {
		texts.editText("letter", string(1, char(int(letter)-32)));
		aniTimer = sf::milliseconds(750.0f) + clock->getElapsedTime();
		texts.editColor("letter", sf::Color::Red);
	}
	texts.displayText(_window, "letter");

}

void TeacherOne::pollInput(Event _event, char _letter)
{
	if ( _letter == remainingLetters->at(remainingLetters->size() - 1)) {//USER INPUT WAS THE CORRECT ASL SYMBOL
		if (*assistance == 2 || *assistance == 3) {
			*score += 1;
			texts.editText("score", "Score: " + to_string(*score) + "/26");
			testCountDown = sf::seconds(6.0f) + clock->getElapsedTime();
		}
		if (remainingLetters->size() == 1) { //IF Z IS ENTERED GO TO MENU
			if (*assistance > 1) {
				ud->saveScore();
				*menu = 3;
			}
			else
				*menu = 2;
		}

		else {//If not Z go to next letter, cLetter is currentLetter as a char
			remainingLetters->pop_back();
			correctTimer = sf::seconds(1.5f) + clock->getElapsedTime();
		}

		texts.editText("letter", string(1, char(int(_letter) - 32)));
		aniTimer = sf::milliseconds(750.0f) + clock->getElapsedTime();
		texts.editColor("letter", sf::Color::Green);
	}
	else if (_event.key.code == 27) {
		if (*assistance > 1) {
			ud->saveScore();
			*menu = 3;
		}
		else
			*menu = 2;
	}

	if ((*assistance == 2 || *assistance == 3) && int(testCountDown.asSeconds() - clock->getElapsedTime().asSeconds()) < 1) {
		failedLetters->push_back(remainingLetters->at(remainingLetters->size() - 1));
		remainingLetters->pop_back();
		incorrectTimer = sf::seconds(1.5f) + clock->getElapsedTime();
		testCountDown = sf::seconds(6.0f) + clock->getElapsedTime();
	}
}
