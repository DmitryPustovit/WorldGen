#include <SFML/Graphics.hpp>
#include "WorldGenerator.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000,1000),"World");
    WorldGenerator _worldGenerator(700,15);
    _worldGenerator.CreateMatrix();
    //_worldGenerator.Interpolate();
    _worldGenerator.createGraphics();
    sf::View view;
    view = window.getView();

    while (window.isOpen()){
        window.clear();
        //view.move(10, 200);
        window.setView(view);
        sf::Event event;
        while (window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                return 0;
            }
        }
        _worldGenerator.Render(&window);
        window.display();



    }
    system("pause");
    return 0;
}