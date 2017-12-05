//
// Created by acurr on 12/1/2017.
//

#include <ctime>
#include <SFML/Graphics/RenderWindow.hpp>
#include "WorldGenerator.h"
#include <math.h>

WorldGenerator::WorldGenerator() {
    this->size = 800;
    srand(static_cast<unsigned int>(time(nullptr)));;
    setUpNoises();
}

WorldGenerator::WorldGenerator(int size) {
    this->size = size;
    srand(static_cast<unsigned int>(time(nullptr)));
    setUpNoises();
}

double WorldGenerator::getNoiseElevation(int x, int y) {
    //Elevation
    double e;
    double nx;
    double ny;
    nx = x / size - .5;
    ny = y / size - .5;
    e = (elevNoise.GetNoise(ny, nx) + 1) / 2 + .5 * (elevNoise.GetNoise(2 * ny, 2 * nx) + 1) / 2 +
        .25 * (elevNoise.GetNoise(4 * ny, 4 * nx) + 1) / 2;
    //e = (elevNoise.GetNoise(ny,nx)+1)/ 2;
    return pow(e, 7);
}

double WorldGenerator::getNoise_Moisture(int x, int y) {
    double m;
    double nx;
    double ny;
    nx = x / size - .5;
    ny = y / size - .5;
    m = (moisNoise.GetNoise(ny, nx) + 1) / 2 + .5 * (moisNoise.GetNoise(2 * ny, 2 * nx) + 1) / 2 +
        .25 * (moisNoise.GetNoise(4 * ny, 4 * nx) + 1) / 2;
    //m = (moisNoise.GetNoise(ny,nx)+1)/ 2;
    return pow(m, 3);
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


void WorldGenerator::Render(sf::RenderWindow *window) {
    for (auto sprit : sprites) {
        window->draw(*sprit);
    }

}

void WorldGenerator::MoveGraphics(float x, float y) {
    for (auto sprit : sprites) {
        sprit->move(x, y);
    }

}

void WorldGenerator::createGraphics() {
    sf::Image image;
    image.create(16, 16);
    for (int y = 0; y < size; y = y + 16) {
        for (int x = 0; x < size; x = x + 16) {
            textures.push_back(new sf::Texture);
            textures[textures.size() - 1]->create(16, 16);
            sprites.push_back(new sf::Sprite);
            for (int ny = y; ny < y + 16; ny++) {
                for (int nx = x; nx < x + 16; nx++) {
                    image.setPixel(ny - y, nx - x, Biome(getNoiseElevation(ny, nx), getNoise_Moisture(ny, nx)));

                }
            }
            textures[textures.size() - 1]->update(image);
            sprites[sprites.size() - 1]->setTexture(*textures[textures.size() - 1]);
            sprites[sprites.size() - 1]->setPosition(y, x);
        }
    }
}

void WorldGenerator::setUpNoises() {
    ///
    elevNoise.SetNoiseType(FastNoise::SimplexFractal);
    elevNoise.SetSeed(rand());
    elevNoise.SetFrequency(5);
    elevNoise.SetFractalOctaves(10);
    elevNoise.SetFractalType(FastNoise::FBM);
    elevNoise.SetFractalLacunarity(2.0);
    elevNoise.SetFractalGain(0.5);
    ///
    moisNoise.SetNoiseType(FastNoise::SimplexFractal);
    moisNoise.SetSeed(rand());
    moisNoise.SetFrequency(3);
    moisNoise.SetFractalOctaves(3);
    moisNoise.SetFractalType(FastNoise::FBM);
    moisNoise.SetFractalLacunarity(2.0);
    moisNoise.SetFractalGain(0.5);
}





