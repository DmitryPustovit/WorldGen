#include "Textbox.h"

//Public
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

void Textbox::draw() {
	window.draw(background);
	window.draw(text);
	window.draw(subtext);
}

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

void Textbox::setString(std::string newString) {
	string = newString;
	text.setString(string);
}

std::string Textbox::getString() {
	return string;
}

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

void Textbox::setSubtext(std::string newString)
{
	subtext.setString(newString);
}

void Textbox::setFocus(bool newFocus) {
	isFocused = newFocus;
	if(newFocus)
		background.setOutlineColor(sf::Color::Red);
	else
		background.setOutlineColor(sf::Color::Black);
}

sf::Vector2i Textbox::getPosition()
{
	return sf::Vector2i(x, y);
}

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
