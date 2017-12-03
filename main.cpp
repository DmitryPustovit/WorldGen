#include <SFML/Graphics.hpp>
#include "WorldGenerator.h"

void renderingThread(sf::RenderWindow *window) {

}
int main()
{
    sf::RenderWindow window(sf::VideoMode(1000,1000),"World");
    WorldGenerator _worldGenerator(800, 15);
    _worldGenerator.CreateMatrix();
    //_worldGenerator.Interpolate();
    _worldGenerator.createGraphics();
    sf::View view;
    view = window.getView();
    sf::Thread thread(&renderingThread, &window);
    thread.launch();
    while (window.isOpen()){
        window.clear();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            view.move(-10, 0);
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
        window.display();


        window.setView(view);
        //std::cout << view.getCenter().y << " " << view.getCenter().x << std::endl;
        sf::Event event;
        while (window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                return 0;
            }
        }


    }
    system("pause");
    return 0;
}