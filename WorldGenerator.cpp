//
// Created by acurr on 12/1/2017.
//

#include <ctime>
#include <SFML/Graphics/RenderWindow.hpp>
#include "WorldGenerator.h"


WorldGenerator::WorldGenerator(int size) {
    int adjustedSize = size;
    if (size % 2 == 1) {
        adjustedSize = size - 1;
    }

    for (int i = 16; i > 1; i--) {
        if (adjustedSize % i == 0) {
            this->transitionSize = i;
            break;
        }
    }
    this->size = adjustedSize;
    _Matrix = new int *[adjustedSize];
    for (int i = 0; i < adjustedSize; i++) {
        _Matrix[i] = new int[adjustedSize];
    }
}

WorldGenerator::WorldGenerator(int size, int trans) {
    int adjustedSize = size;
    if (size % 2 == 1) {
        adjustedSize = size - 1;
    }
    transitionSize = trans;
    this->size = adjustedSize;
    _Matrix = new int *[adjustedSize];
    for (int i = 0; i < adjustedSize; i++) {
        _Matrix[i] = new int[adjustedSize];
    }
}

void WorldGenerator::CreateMatrix() {
    srand(static_cast<unsigned int>(time(nullptr)));
    for (int y = 0; y < size - 1; y = y + transitionSize) {
        for (int x = 0; x < size - 1; x = x + transitionSize) {
            _Matrix[y][x] = rand() % 100;
        }
    }
}

void WorldGenerator::Interpolate() {
    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size - transitionSize; x = x + transitionSize) {
            auto Difference = static_cast<float>(_Matrix[y][x + transitionSize] - _Matrix[y][x]);
            float InterpolationValue = Difference / transitionSize;
            int counter = 0;
            for (int c = x; c < x + transitionSize; c++) {
                _Matrix[y][c] = static_cast<int>(_Matrix[y][x] + (InterpolationValue * counter));
                counter++;

            }

        }
    }

    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size - transitionSize; y = y + transitionSize) {
            auto Difference = static_cast<float>(_Matrix[y + transitionSize][x] - _Matrix[y][x]);
            float InterpolationValue = Difference / transitionSize;
            int counter = 0;
            for (int c = y; c < y + transitionSize; c++) {
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
    for (int y = 0; y < size - 1; y++) {
        for (int x = 0; x < size - 1; x++) {
            _Graphics.push_back(new sf::RectangleShape);
            _Graphics[_Graphics.size() - 1]->setSize(sf::Vector2<float>(10.0f, 10.0f));
            _Graphics[_Graphics.size() - 1]->setPosition(x * 10.0f, y * 10.0f);

            //Water
            if (_Matrix[y][x] < 35) {
                _Graphics[_Graphics.size() - 1]->setFillColor(sf::Color(0, 157, 255));
            }
            //sand
            if (_Matrix[y][x] > 34 && _Matrix[y][x] < 50) {
                _Graphics[_Graphics.size() - 1]->setFillColor(sf::Color(255, 230, 0));
            }
            //Grass
            if (_Matrix[y][x] > 49 && _Matrix[y][x] < 85) {
                _Graphics[_Graphics.size() - 1]->setFillColor(sf::Color(0, 145, 0));
            }
            //Rocks - Stones
            if (_Matrix[y][x] > 84) {
                _Graphics[_Graphics.size() - 1]->setFillColor(sf::Color(80, 80, 80));
            }
        }

    }

}
