#include <SFML/Graphics.hpp>
#include "WorldGenerator.h"

void zoomViewAt(sf::Vector2i pixel, sf::RenderWindow &window, float zoom, WorldGenerator _worldGenerator) {
    const sf::Vector2f beforeCoord{window.mapPixelToCoords(pixel)};
    sf::View view{window.getView()};
    view.zoom(zoom);
    window.setView(view);
    const sf::Vector2f afterCoord{window.mapPixelToCoords(pixel)};
    const sf::Vector2f offsetCoords{beforeCoord - afterCoord};
    _worldGenerator.MoveGraphics(offsetCoords.x, offsetCoords.y);
}

int main()
{

    sf::RenderWindow window(sf::VideoMode(800, 800), "World");
    WorldGenerator _worldGenerator(800);
    _worldGenerator.createGraphics();
    sf::View view;
    float moveSpeed = .1;
    view.setSize(900, 900);
    window.setView(view);
    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                return 0;
            }
            if (event.type == sf::Event::MouseWheelScrolled) {
                if (event.mouseWheelScroll.delta > 0)
                    zoomViewAt({event.mouseWheelScroll.x, event.mouseWheelScroll.y}, window, (1.f / .9),
                               _worldGenerator);
                else if (event.mouseWheelScroll.delta < 0)
                    zoomViewAt({event.mouseWheelScroll.x, event.mouseWheelScroll.y}, window, .9, _worldGenerator);
            }
        }
        window.clear();
        view = window.getView();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            _worldGenerator.MoveGraphics(-moveSpeed, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            _worldGenerator.MoveGraphics(moveSpeed, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            _worldGenerator.MoveGraphics(0, -moveSpeed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            _worldGenerator.MoveGraphics(0, moveSpeed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageUp)) {
            view.setSize(view.getSize().x * 0.9f, view.getSize().y * 0.9f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageDown)) {
            view.setSize(view.getSize().x * 1.1f, view.getSize().y * 1.1f);
        }
        _worldGenerator.Render(&window);
        window.setView(view);
        window.display();
    }
    system("pause");
    return 0;
}