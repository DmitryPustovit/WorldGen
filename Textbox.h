#ifndef Textbox_cpp
#define Textbox_cpp

#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>

class Textbox {
public:
	Textbox(sf::RenderWindow &windowToUse, sf::Font &fontToUse);
	void Textbox::setDimensons(int inputX, int inputY, int inputWidth, int inputHeight);
	void draw();
	void setString(std::string newString);
	void setSubtext(std::string newString);
	std::string getString();
	sf::Vector2i Textbox::getPosition();
	sf::Vector2i Textbox::getDimentions();
	void pollEvent(sf::Event event, sf::Vector2i mouse);
	void setFocus(bool newFocus);

private:
	bool isFocused;
	int x;
	int y;
	int width;
	int height;
	std::string string = "";
	sf::Font &font;
	sf::RenderWindow &window;
	sf::RectangleShape background;
	sf::Text text;
	sf::Text subtext;
	
	void enterText(sf::Uint32 unicode);
};

#endif