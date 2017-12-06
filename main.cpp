#include <SFML/Graphics.hpp>
#include "WorldGenerator.h"

WorldGenerator _worldGenerator;

void zoomViewAt(sf::Vector2i pixel, sf::RenderWindow &window, float zoom) {
    sf::View view{window.getView()};
    view.zoom(zoom);
    window.setView(view);
    window.setView(view);
}

void renderingThread(sf::RenderWindow *window) {
    // the rendering loop
    window->setActive(true);
    while (window->isOpen()) {
        // draw...
        window->clear();
        _worldGenerator.Render(window);
        window->display();
    }
}
int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "World");
    int size = 1000;
    _worldGenerator = WorldGenerator(size);
    _worldGenerator.createGraphics();
    sf::View view;
    float moveSpeed = size * .00001;
    view.setSize(900, 900);
    window.setView(view);
    window.setActive(false);

    // launch the rendering thread
    sf::Thread thread(&renderingThread, &window);
    thread.launch();


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
            view.setSize(view.getSize().x * 0.999999f, view.getSize().y * 0.999999f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageDown)) {
            view.setSize(view.getSize().x * 1.00001f, view.getSize().y * 1.00001f);
        }
        //_worldGenerator.Render(&window);
        window.setView(view);
        //window.display();
    }
    system("pause");
    return 0;
}