//
// Created by acurr on 12/1/2017.
//

#include <ctime>
#include <SFML/Graphics/RenderWindow.hpp>
#include "WorldGenerator.h"
#include "FastNoise.h"
#include <math.h>

WorldGenerator::WorldGenerator() {
    this->size = 500;
    _Elevation = new double *[500];
    for (int i = 0; i < size; i++) {
        _Elevation[i] = new double[500];
    }
}

WorldGenerator::WorldGenerator(int size) {
    this->size = size;
    _Elevation = new double *[size];
    for (int i = 0; i < size; i++) {
        _Elevation[i] = new double[size];
    }
}

WorldGenerator::WorldGenerator(int size, int trans) {
    transitionSize = trans;
    this->size = size;
    _Elevation = new double *[size]; //make them into one array 3d [y][x][{e,m}]
    _Moisture = new double *[size];
    for (int i = 0; i < size; i++) {
        _Elevation[i] = new double[size];
        _Moisture[i] = new double[size];
    }
}

void WorldGenerator::CreateMatrix() {
    srand(time(nullptr));
    //Elevation
    FastNoise elevNoise;
    elevNoise.SetNoiseType(FastNoise::SimplexFractal);
    elevNoise.SetSeed(rand());
    elevNoise.SetFrequency(5);
    elevNoise.SetFractalOctaves(10);
    elevNoise.SetFractalType(FastNoise::FBM);
    elevNoise.SetFractalLacunarity(2.0);
    elevNoise.SetFractalGain(0.5);
    //Moist
    FastNoise moisNoise;
    moisNoise.SetNoiseType(FastNoise::SimplexFractal);
    moisNoise.SetSeed(rand());
    moisNoise.SetFrequency(3);
    moisNoise.SetFractalOctaves(3);
    moisNoise.SetFractalType(FastNoise::FBM);
    moisNoise.SetFractalLacunarity(2.0);
    moisNoise.SetFractalGain(0.5);
    srand(static_cast<unsigned int>(time(nullptr)));
    double e;
    double m;
    double nx;
    double ny;
    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            nx = x / size - .5;
            ny = y / size - .5;
            e = (elevNoise.GetNoise(ny, nx) + 1) / 2 + .5 * (elevNoise.GetNoise(2 * ny, 2 * nx) + 1) / 2 +
                .25 * (elevNoise.GetNoise(4 * ny, 4 * nx) + 1) / 2;
            //e = (elevNoise.GetNoise(ny,nx)+1)/ 2;
            m = (moisNoise.GetNoise(ny, nx) + 1) / 2 + .5 * (moisNoise.GetNoise(2 * ny, 2 * nx) + 1) / 2 +
                .25 * (moisNoise.GetNoise(4 * ny, 4 * nx) + 1) / 2;
            //m = (moisNoise.GetNoise(ny,nx)+1)/ 2;
            _Elevation[y][x] = pow(e, 10);
            _Moisture[y][x] = pow(m, 3);
        }
    }
}

sf::Color WorldGenerator::Biome(double e, double m) {
    if (e < 0.025)
        return sf::Color(0, 136, 217); //DEEPER_OCEAN
    if (e < 0.05)
        return sf::Color(0, 147, 234); //DEEP_OCEAN
    if (e < 0.1)
        return sf::Color(0, 157, 255); //OCEAN
    if (e < 0.12) {
        //BEACH
        return sf::Color(255, 230, 0);
    }
    if (e > 0.3) {
        if (m < 0.16) {
            //TEMPERATE_DESERT;
            return sf::Color(230, 247, 134);
        }
        if (m < 0.50) {
            //GRASSLAND;
            return sf::Color(0, 145, 0);
        }
        if (m < 0.83) {
            //TEMPERATE_DECIDUOUS_FOREST;
            return sf::Color(60, 247, 69);
        }
        //TEMPERATE_RAIN_FOREST;
        return sf::Color(60, 247, 157);
    }
    if (e > 0.6) {
        if (m < 0.33) {
            //TEMPERATE_DESERT
            return sf::Color(230, 247, 134);
        }

        if (m < 0.66) {
            //SHRUBLAND
            return sf::Color(190, 242, 138);
        }
        //TAIGA;
        return sf::Color(143, 234, 128);
    }
    if (e > 0.8) {
        if (m < 0.1) {
            //SCORCHED
            return sf::Color(255, 244, 149);
        }
        if (m < 0.2) {
            //BARE;
            return sf::Color(255, 251, 215);
        }
        if (m < 0.5) {
            //TUNDRA
            return sf::Color(215, 255, 155);
        }
        //SNOW;
        return sf::Color(235, 235, 235);
    }
    if (m < 0.16) {
        //SUBTROPICAL_DESERT;
        return sf::Color(233, 216, 97);
    }
    if (m < 0.33) {
        //GRASSLAND
        return sf::Color(0, 145, 0);
    }
    if (m < 0.66) {
        //TROPICAL_SEASONAL_FOREST
        return sf::Color(132, 213, 117);
    }
    //TROPICAL_RAIN_FOREST
    return sf::Color(123, 206, 130);;
}

/*void WorldGenerator::Interpolate() {
    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size - transitionSize; x = x + transitionSize) {
            auto Difference = static_cast<float>(_Elevation[y][x + transitionSize] - _Elevation[y][x]);
            float InterpolationValue = Difference / transitionSize;
            int counter = 0;
            for (int c = x; c < x + transitionSize; c++) {
                _Elevation[y][c] = static_cast<int>(_Elevation[y][x] + (InterpolationValue * counter));
                counter++;

            }

        }
    }

    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size - transitionSize; y = y + transitionSize) {
            auto Difference = static_cast<float>(_Elevation[y + transitionSize][x] - _Elevation[y][x]);
            float InterpolationValue = Difference / transitionSize;
            int counter = 0;
            for (int c = y; c < y + transitionSize; c++) {
                _Elevation[c][x] = static_cast<int>(_Elevation[y][x] + (InterpolationValue * counter));
                counter++;

            }

        }
    }
}*/

void WorldGenerator::Render(sf::RenderWindow *window) {
    int count = 0;
    for (auto &_Graphic : _Graphics) {
		window->draw(*_Graphic);
        if (window->getView().getSize().x >= (_Graphic->getPosition().x + _Graphic->getSize().x) &&
            window->getView().getSize().y >= (_Graphic->getPosition().y + _Graphic->getSize().y)) {
            count++;
        }
		//window->clear();
		//window->display();
    }
    //std::cout << count <<std::endl;


}

void WorldGenerator::createGraphics(sf::RenderWindow *window) {
    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            _Graphics.push_back(new sf::RectangleShape);
            _Graphics[_Graphics.size() - 1]->setSize(sf::Vector2<float>(1.0f, 1.0f));
            _Graphics[_Graphics.size() - 1]->setPosition(x * 1.0f, y * 1.0f);
            _Graphics[_Graphics.size() - 1]->setFillColor(Biome(_Elevation[y][x], _Moisture[y][x]));
			window->clear();
			Render(window);
			window->display();

        }

    }

}



