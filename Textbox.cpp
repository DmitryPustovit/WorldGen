#include "Textbox.h"

/**
* Creates textbox for UI use
*
* @param windowToUse
* @param fontToUse
*
* @return none
*/
Textbox::Textbox(sf::RenderWindow &windowToUse, sf::Font &fontToUse) : window(windowToUse), font(fontToUse) {
	text = sf::Text("", font);
	background.setFillColor(sf::Color::White);
	background.setOutlineColor(sf::Color::Black);
	background.setOutlineThickness(4);
	text.setFillColor(sf::Color::Black);
	subtext = sf::Text("", font);
	subtext.setFillColor(sf::Color::Black);
	subtext.setCharacterSize(24);
}

/**
* Draws textbox and associated text to screen
*
* @param none
*
* @return none
*/
void Textbox::draw() {
	window.draw(background);
	window.draw(text);
	window.draw(subtext);
}

/**
* Sets the textbox dimentions, both location and size
*
* @param inputX
* @param inputY
* @param inputWidth
* @param inputHeight
*
* @return none
*/
void Textbox::setDimensons(int inputX, int inputY, int inputWidth, int inputHeight) {
	x = inputX;
	y = inputY;
	width = inputWidth;
	height = inputHeight;
	text.setPosition(x, y - height / 5);
	text.setCharacterSize(height);
	subtext.setPosition(inputX, inputY - 40);
	background.setPosition(x, y);
	background.setSize(sf::Vector2f(width, height));
}


/**
* Sets the string inside the textbox
*
* @param string
*
* @return none
*/
void Textbox::setString(std::string newString) {
	string = newString;
	text.setString(string);
}

/**
* Gets the string inside of the textbox
*
* @param none
*
* @return string
*/
std::string Textbox::getString() {
	return string;
}

/**
* Update method for textbox
* Writes to textbox
* Check for textbox click to set active / inactive
*
* @param event
* @param mouse
*
* @return none
*/
void Textbox::pollEvent(sf::Event event, sf::Vector2i mouse) {
	if (isFocused) {
		if (event.type == sf::Event::TextEntered)
			enterText(event.text.unicode);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)
			&& (mouse.x < Textbox::getPosition().x
				|| mouse.x > Textbox::getPosition().x + Textbox::getDimentions().x
				|| mouse.y < Textbox::getPosition().y
				|| mouse.y > Textbox::getPosition().y + Textbox::getDimentions().y))
		{
			Textbox::setFocus(false);
		}
	}
	else {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)
			&& mouse.x >= Textbox::getPosition().x
			&& mouse.x <= Textbox::getPosition().x + Textbox::getDimentions().x
			&& mouse.y >= Textbox::getPosition().y
			&& mouse.y <= Textbox::getPosition().y + Textbox::getDimentions().y)
		{
			Textbox::setFocus(true);
		}

	}
}

/**
* Sets the textbox title/helper text
*
* @param newString
*
* @return none
*/
void Textbox::setSubtext(std::string newString)
{
	subtext.setString(newString);
}

/**
* Sets the textbox focus to true or false
*
* @param newFocus
*
* @return none
*/
void Textbox::setFocus(bool newFocus) {
	isFocused = newFocus;
	if(newFocus)
		background.setOutlineColor(sf::Color::Red);
	else
		background.setOutlineColor(sf::Color::Black);
}

/**
* Gets the textbox's current pixel location
*
* @param none
*
* @return position
*/
sf::Vector2i Textbox::getPosition()
{
	return sf::Vector2i(x, y);
}

/**
* Gets the textbox's current size
*
* @param none
*
* @return dimetions
*/
sf::Vector2i Textbox::getDimentions()
{
	return sf::Vector2i(width, height);
}


//private
void Textbox::enterText(sf::Uint32 unicode) {
	if(unicode == 8)
		string = string.substr(0, string.length()-1); // delete key
	else
		string += (char) unicode;
	text.setString(string);
}
