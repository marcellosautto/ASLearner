#pragma once
#include "pch.h"
#include "SpriteManager.h"

// A class that creates a UI button out of a sprite that can then be clicked to make things happen
class ButtonManager
{
protected:
	bool pState = false;
	bool isPressed = false;
	bool wasPressed = false;
	bool sticky = false;

	SpriteManager mng;
	sf::Color color = sf::Color(100, 100, 100);
	sf::Color sColor = sf::Color(100, 100, 100);
	sf::SoundBuffer playClickB, defaultClickB;
	sf::Sound playClickS, defaultClickS;

public:
	ButtonManager(std::string _filepath, float _x, float _y, float _scale = 1);
	ButtonManager(std::string _filepath, float _x, float _y, float _scale, sf::Color _stickyColor, bool _stick);
	bool IsPressed(),
		isStuck();
	void SetPressColor(sf::Color _color),
		SetStickyColor(sf::Color _color);
	void SetSprite(std::string _filepath);
	void DrawButton(sf::RenderWindow& _window);
	void Stick(bool _sticky);
};

