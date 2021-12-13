#include "pch.h"
#include "TextManager.h"

TextManager::TextManager()
{
	for (const auto& entry : directory_iterator("Assets\\Fonts")) {

		Font font;

		if (!font.loadFromFile(entry.path().string()))
			errorMessageExit("Failed to load font");

		string path = entry.path().filename().string();
		fontMap[path.substr(0, path.size() - 4)] = font;
	}
}

void TextManager::createText(string _name, string _text, string _font, Color _color,int _size, float _xPos, float _yPos)
{
	Text text;
	text.setString(_text);
	if(fontMap.find(_font) == fontMap.end())
		errorMessageExit("Failed to locate font");
	text.setFont(fontMap[_font]);
	text.setFillColor(_color);
	text.setCharacterSize(_size);
	text.setPosition(_xPos, _yPos);
	textMap[_name] = text;
}

void TextManager::editColor(string _name, sf::Color _color)
{
	textMap[_name].setFillColor(_color);
}

void TextManager::displayText(RenderTarget& _window, string _name)
{
	_window.draw(textMap[_name]);
}

void TextManager::editText(string _name, string _text)
{
	textMap[_name].setString(_text);
}

void TextManager::displayText(RenderTarget &_window)
{
	for (std::pair<std::string, sf::Text> pair : textMap) {
		_window.draw(pair.second);
	}
}

void TextManager::setTextStyle(string _name, Text::Style _style)
{
	textMap[_name].setStyle(_style);
}