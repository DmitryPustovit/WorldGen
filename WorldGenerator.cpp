//
// Created by acurr on 12/1/2017.
//

#include <ctime>
#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>
#include "WorldGenerator.h"

void WorldGenerator::CreateMatrix() {
    srand(static_cast<unsigned int>(time(nullptr)));
    for(int y = 0;y < 408;y =y+8){
        for(int x = 0; x < 408;x = x+8){
            _Matrix[y][x] = rand()%100;
        }

    }
}
void WorldGenerator::Interpolate() {
    for(int y = 0;y < 408; y++){
        for(int x = 0; x < 408;x =x+8){
            auto Difference = static_cast<float>(_Matrix[y][x+8] - _Matrix[y][x]) ;
                float InterpolationValue = Difference / 8.0f;
                int counter = 0;
                for(int c = x;c < x+8;c++){
                    _Matrix[y][c] = static_cast<int>(_Matrix[y][x] + (InterpolationValue * counter));
                    counter++;

            }

        }
    }

    for(int x = 0; x < 408;x++){
        for(int y = 0;y < 408; y=y+8){
            auto Difference = static_cast<float>(_Matrix[y+8][x] - _Matrix[y][x]) ;
            float InterpolationValue = Difference / 8.0f;
            int counter = 0;
            for(int c = y;c <y+8;c++){
                _Matrix[c][x] = static_cast<int>(_Matrix[y][x] + (InterpolationValue * counter));
                counter++;

            }

        }
    }
}

void WorldGenerator::Render(sf::RenderWindow *window) {
    for (auto &_Graphic : _Graphics) {
        window->draw(*_Graphic);
    }

}

void WorldGenerator::createGraphics() {
    for(int y = 0;y < 408; y++){
        for(int x = 0; x < 408;x++){
            _Graphics.push_back(new sf::RectangleShape);
            _Graphics[_Graphics.size()-1]->setSize(sf::Vector2<float>(10.0f, 10.0f));
            _Graphics[_Graphics.size()-1]->setPosition(x*10.0f,y*10.0f);

            //Water
            if(_Matrix[y][x] < 35){
                _Graphics[_Graphics.size()-1]->setFillColor(sf::Color(0,157,255));
            }
            //sand
            if(_Matrix[y][x] > 34 && _Matrix[y][x] < 50){
                _Graphics[_Graphics.size()-1]->setFillColor(sf::Color(255,230,0));
            }
            //Grass
            if(_Matrix[y][x] > 49 && _Matrix[y][x] < 85){
                _Graphics[_Graphics.size()-1]->setFillColor(sf::Color(0,145,0));
            }
            //Rocks - Stones
            if(_Matrix[y][x] > 84){
                _Graphics[_Graphics.size()-1]->setFillColor(sf::Color(80,80,80));
            }
    }

    }

}
