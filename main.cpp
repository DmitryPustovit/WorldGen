#include <SFML/Graphics.hpp>
#include "WorldGenerator.h"

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

int main()
{

    sf::RenderWindow window(sf::VideoMode(800, 800), "World");
    WorldGenerator _worldGenerator(800, 15);
    //_worldGenerator.CreateMatrix();
    //_worldGenerator.Interpolate();
    _worldGenerator.createGraphics();
    sf::View view;
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
        window.clear();
        view = window.getView();
        //view.setCenter(window.getSize().x/2,window.getSize().y/2);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            view.setCenter(view.getCenter().x - 10, view.getCenter().y);
            //view.move(-10, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            view.move(10, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            view.move(0, -10);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            view.move(0, 10);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageUp)) {
            view.zoom(0.9f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageDown)) {
            view.zoom(1.1f);
        }

        _worldGenerator.Render(&window);
        window.setView(view);
        window.display();



        //std::cout << view.getCenter().y << " " << view.getCenter().x << std::endl;



    }
    system("pause");
    return 0;
}