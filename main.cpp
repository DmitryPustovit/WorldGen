#include <SFML/Graphics.hpp>
#include "WorldGenerator.h"
#include <iostream>

using namespace std;

//sf::VideoMode desktop = sf::VideoMode().getDesktopMode();
sf::RenderWindow window(sf::VideoMode(400, 400), "Adventure!");

void zoomViewAt(sf::Vector2i pixel, sf::RenderWindow &window, float zoom) {
    const sf::Vector2f beforeCoord{window.mapPixelToCoords(pixel)};
    sf::View view{window.getView()};
    view.zoom(zoom);
    window.setView(view);
    const sf::Vector2f afterCoord{window.mapPixelToCoords(pixel)};
    const sf::Vector2f offsetCoords{beforeCoord - afterCoord};
    view.move(offsetCoords);
    window.setView(view);
}

void updateRender(sf::View view, WorldGenerator wg)
{
	window.clear();
	window.setView(view);
	wg.Render(&window);
	window.display();
}

int main()
{
	window.setFramerateLimit(0);
	window.setVerticalSyncEnabled(false);
    sf::View view;
	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
	{
		cout << "Font Load Error" << endl;
		return EXIT_FAILURE;
	}
	sf::RectangleShape rectangle(sf::Vector2f(window.getSize().x, 50));
	rectangle.setFillColor(sf::Color::Black);
	sf::Text text("Debug On", font, 40);
	sf::Text loading("Generating World", font, 40);
	loading.setOutlineColor(sf::Color::White);
	window.draw(loading);
	window.display();
	loading.setFillColor(sf::Color::Black);
	text.setFillColor(sf::Color::Red);
	bool debug = false;
	//Creation of World
	WorldGenerator _worldGenerator(80, 15);
	_worldGenerator.CreateMatrix();
	//_worldGenerator.Interpolate();
	view.setSize(400, 400);
	window.setView(view);
	_worldGenerator.createGraphics(&window);

	//Update
    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                return 0;
            }
            if (event.type == sf::Event::MouseWheelScrolled) {
                if (event.mouseWheelScroll.delta > 0)
                    zoomViewAt({event.mouseWheelScroll.x, event.mouseWheelScroll.y}, window, (1.f / .9));
                else if (event.mouseWheelScroll.delta < 0)
                    zoomViewAt({event.mouseWheelScroll.x, event.mouseWheelScroll.y}, window, .9);
            }
        }
        view = window.getView();
        //view.setCenter(window.getSize().x/2,window.getSize().y/2);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            view.setCenter(view.getCenter().x - 10, view.getCenter().y);
            //view.move(-10, 0);
			updateRender(view, _worldGenerator);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            view.move(10, 0);
			updateRender(view, _worldGenerator);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            view.move(0, -10);
			updateRender(view, _worldGenerator);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            view.move(0, 10);
			updateRender(view, _worldGenerator);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageUp)) {
            view.zoom(0.9f);
			updateRender(view, _worldGenerator);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageDown)) {
            view.zoom(1.1f);
			updateRender(view, _worldGenerator);
        }

		//Debug for those of us that don't have Page Up and Down keys
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
			view.zoom(0.9f);
			updateRender(view, _worldGenerator);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
			view.zoom(1.1f);
			updateRender(view, _worldGenerator);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F3)) {
			if (debug)
				debug = false;
			else
				debug = true;
		}
        
		if (debug)
		{
			window.clear();
			window.draw(rectangle);
			window.draw(text);
			window.setView(view);
			window.display();
		}




        //std::cout << view.getCenter().y << " " << view.getCenter().x << std::endl;



    }

	//Application Close
    system("pause");
    return 0;
}