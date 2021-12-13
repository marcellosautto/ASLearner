#pragma once

using namespace sf;
class TextManager {

public:

	TextManager();

	void createText(string _name, string _text, string _font, Color _color, int _size, float _xPos, float _yPos),
		setTextStyle(string _name, Text::Style _style),
		displayText(RenderTarget &_window),
		displayText(RenderTarget& _window, string _name),
		editText(string _name, string _text),
		editColor(string _name, sf::Color _color);


private:

	unordered_map<string, Text> textMap;
	unordered_map<string, Font> fontMap;
};