#include "pch.h"
#include "ButtonManager.h"

ButtonManager::ButtonManager(std::string _filepath, float _x, float _y, float _scale) {
	// Initialize the sprite
	SetSprite(_filepath);
	sf::Sprite& sprite = mng.GetSprite("button");
	sprite.setPosition(_x, _y);
	sprite.setScale(_scale, _scale);

	if (!playClickB.loadFromFile("Assets/Audio/p_click.wav"))
		errorMessageExit("Sound Load Fail");

	if (!defaultClickB.loadFromFile("Assets/Audio/click.wav"))
		errorMessageExit("Sound Load Fail");

	playClickS.setBuffer(playClickB);
	defaultClickS.setBuffer(defaultClickB);
}
ButtonManager::ButtonManager(std::string _filepath, float _x, float _y, float _scale, sf::Color _stickyColor, bool _stick) {
	// Initialize the sprite
	SetSprite(_filepath);
	sf::Sprite& sprite = mng.GetSprite("button");
	sprite.setPosition(_x, _y);
	sprite.setScale(_scale, _scale);

	if (!playClickB.loadFromFile("Assets/Audio/p_click.wav"))
		errorMessageExit("Sound Load Fail");

	if (!defaultClickB.loadFromFile("Assets/Audio/click.wav"))
		errorMessageExit("Sound Load Fail");

	playClickS.setBuffer(playClickB);
	defaultClickS.setBuffer(defaultClickB);
	
	SetStickyColor(_stickyColor);
	sticky = _stick;
}
bool ButtonManager::IsPressed() {
	// returns true only when the button is released
	return (wasPressed && !isPressed) ? true : false;
}
bool ButtonManager::isStuck()
{
	return sticky;
}
void ButtonManager::SetPressColor(sf::Color _color) {
	// sets the color that the button becomes when a user clicks it
	color = _color;
}
void ButtonManager::SetStickyColor(sf::Color _color) {
	// sets the color that the button becomes when a user clicks it
	sColor = _color;
}
void ButtonManager::SetSprite(std::string _filepath) {
	// Stores sprite in the manager
	mng.CreateSprite("button", _filepath);
}
void ButtonManager::DrawButton(sf::RenderWindow& _window) {
	// Update the previous state of the button
	wasPressed = isPressed;

	// Check if the user has clicked on the button sprite
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && sf::Mouse::getPosition(_window).x > mng.GetSprite("button").getPosition().x && sf::Mouse::getPosition(_window).x < mng.GetSprite("button").getPosition().x + mng.GetSprite("button").getGlobalBounds().width && sf::Mouse::getPosition(_window).y > mng.GetSprite("button").getPosition().y && sf::Mouse::getPosition(_window).y < mng.GetSprite("button").getPosition().y + mng.GetSprite("button").getGlobalBounds().height)
		isPressed = true;
	else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
		isPressed = false;

	// Visually change the color of the button when it is pressed
	if (isPressed) {
		mng.GetSprite("button").setColor(color);
		if (mng.GetSprite("button").getPosition() == sf::Vector2f(380, 400))
			playClickS.play();
		else
			defaultClickS.play();
	}
	else if (sticky) {
		mng.GetSprite("button").setColor(sColor);
	}
	else
		mng.GetSprite("button").setColor(sf::Color::White);

	// Draw the button to screen
	_window.draw(mng.GetSprite("button"));
}
void ButtonManager::Stick(bool _sticky)
{
	sticky = _sticky;
}
