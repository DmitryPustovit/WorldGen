//
// Created by acurr on 12/1/2017.
//

#include <ctime>
#include <SFML/Graphics/RenderWindow.hpp>
#include "WorldGenerator.h"
#include <cmath>

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
    if (e > 1) {
        return 1;
    }
    return e;
}

double WorldGenerator::getNoiseTempature(int x, int y) {
    //Elevation
    double t;
    double nx;
    double ny;
    nx = x / size - .5;
    ny = y / size - .5;
    t = (tempNoise.GetNoise(ny, nx) + 1) / 2 + .5 * (tempNoise.GetNoise(2 * ny, 2 * nx) + 1) / 2 +
        .25 * (tempNoise.GetNoise(4 * ny, 4 * nx) + 1) / 2;
    //t = (elevNoise.GetNoise(ny,nx)+1)/ 2;
    return pow(t, 7);
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
    return pow(m, 4);
}

sf::Color WorldGenerator::Biome(double e, double m, double t) {
    if (t < 0.05)
        return sf::Color(0, e * 136, e * 217); //DEEPER_OCEAN
    if (t < 0.10)
        return sf::Color(0, e * 147, e * 234); //DEEP_OCEAN
    if (t < 0.15)
        return sf::Color(0, e * 157, e * 255); //OCEAN
    if (t < 0.20) {
        //BEACH
        return sf::Color(e * 255, e * 230, 0);
    }
    if (t > 0.3) {
        if (m < 0.16) {
            //TEMPERATE_DESERT;
            return sf::Color(e * 230, e * 247, e * 134);
        }
        if (m < 0.50) {
            //GRASSLAND;
            return sf::Color(0, e * 145, 0);
        }
        if (m < 0.83) {
            //TEMPERATE_DECIDUOUS_FOREST;
            return sf::Color(e * 60, e * 247, e * 69);
        }
        //TEMPERATE_RAIN_FOREST;
        return sf::Color(e * 60, e * 247, e * 157);
    }
    if (t > 0.6) {
        if (m < 0.33) {
            //TEMPERATE_DESERT
            return sf::Color(e * 230, e * 247, e * 134);
        }
        if (m < 0.66) {
            //SHRUBLAND
            return sf::Color(e * 190, e * 242, e * 138);
        }
        //TAIGA;
        return sf::Color(e * 143, e * 234, e * 128);
    }
    if (t > 0.8) {
        if (m < 0.1) {
            //SCORCHED
            return sf::Color(e * 255, e * 244, e * 149);
        }
        if (m < 0.2) {
            //BARE;
            return sf::Color(e * 255, e * 251, e * 215);
        }
        if (m < 0.5) {
            //TUNDRA
            return sf::Color(e * 215, e * 255, e * 155);
        }
        //SNOW;
        return sf::Color(e * 255, e * 255, e * 255);
    }
    if (m < 0.16) {
        //SUBTROPICAL_DESERT;
        return sf::Color(e * 233, e * 216, e * 97);
    }
    if (m < 0.33) {
        //GRASSLAND
        return sf::Color(0, e * 145, 0);
    }
    if (m < 0.66) {
        //TROPICAL_SEASONAL_FOREST
        return sf::Color(e * 132, e * 213, e * 117);
    }
    //TROPICAL_RAIN_FOREST
    return sf::Color(e * 123, e * 206, e * 130);;
}



void WorldGenerator::Render(sf::RenderWindow *window) {
    for (auto sprit : sprites) {
        if (window->getView().getSize().x + window->getPosition().x + 400 >=
            sprit->getPosition().x + sprit->getTexture()->getSize().x &&
            window->getView().getSize().y + window->getPosition().y + 400 >=
            sprit->getPosition().y + sprit->getTexture()->getSize().y) {
            window->draw(*sprit);
        }
    }

}

void WorldGenerator::MoveGraphics(float x, float y) {
    for (auto sprit : sprites) {
        sprit->move(x, y);
    }
    lastCreatedx += x;
    lastCreatedy += y;
    /*std::cout << lastCreatedx<< std::endl;
    if(lastCreatedx == 0 || lastCreatedy == 0){

        createNewGraphics();
    }*/



}
void WorldGenerator::createGraphics() {
    sf::Image image;
    image.create(16, 16);
    int yy = lastCreatedy;
    int xx = lastCreatedx;
    for (int y = yy; y < size; y = y + 16) {
        for (int x = xx; x < size; x = x + 16) {
            textures.push_back(new sf::Texture);
            textures[textures.size() - 1]->create(16, 16);
            sprites.push_back(new sf::Sprite);
            for (int ny = y; ny < y + 16; ny++) {
                for (int nx = x; nx < x + 16; nx++) {
                    image.setPixel(ny - y, nx - x, Biome(getNoiseElevation(ny, nx), getNoise_Moisture(ny, nx),
                                                         getNoiseTempature(ny, nx)));
                }
            }
            textures[textures.size() - 1]->update(image);
            sprites[sprites.size() - 1]->setTexture(*textures[textures.size() - 1]);
            sprites[sprites.size() - 1]->setPosition(y, x);
            lastCreatedx = sprites[sprites.size() - 1]->getPosition().x;
        }
        lastCreatedy = sprites[sprites.size() - 1]->getPosition().y;
    }
}


void WorldGenerator::createNewGraphics() {
    sf::Image image;
    image.create(16, 16);
    int yy = lastCreatedy;
    int xx = lastCreatedx;
    for (int y = 0; y <= yy + 16; y = y + 16) {
        for (int x = xx; x <= xx + 16; x = x + 16) {
            textures.push_back(new sf::Texture);
            textures[textures.size() - 1]->create(16, 16);
            sprites.push_back(new sf::Sprite);
            for (int ny = y; ny < y + 16; ny++) {
                for (int nx = x; nx < x + 16; nx++) {
                    image.setPixel(ny - y, nx - x, Biome(getNoiseElevation(ny, nx), getNoise_Moisture(ny, nx),
                                                         getNoiseTempature(ny, nx)));
                }
            }
            textures[textures.size() - 1]->update(image);
            sprites[sprites.size() - 1]->setTexture(*textures[textures.size() - 1]);
            sprites[sprites.size() - 1]->setPosition(y, x);
            lastCreatedx = x;
        }
        lastCreatedy = y;
    }
    for (int y = yy; y <= yy + 16; y = y + 16) {
        for (int x = 0; x <= xx + 16; x = x + 16) {
            textures.push_back(new sf::Texture);
            textures[textures.size() - 1]->create(16, 16);
            sprites.push_back(new sf::Sprite);
            for (int ny = y; ny < y + 16; ny++) {
                for (int nx = x; nx < x + 16; nx++) {
                    image.setPixel(ny - y, nx - x, Biome(getNoiseElevation(ny, nx), getNoise_Moisture(ny, nx),
                                                         getNoiseTempature(ny, nx)));
                }
            }
            textures[textures.size() - 1]->update(image);
            sprites[sprites.size() - 1]->setTexture(*textures[textures.size() - 1]);
            sprites[sprites.size() - 1]->setPosition(y, x);
            lastCreatedx = x;
        }
        lastCreatedy = y;
    }
}

void WorldGenerator::setUpNoises() {
    ///
    elevNoise.SetNoiseType(FastNoise::SimplexFractal);
    elevNoise.SetSeed(rand());
    elevNoise.SetFrequency(5);
    elevNoise.SetFractalOctaves(10);
    elevNoise.SetFractalType(FastNoise::FBM);
    elevNoise.SetFractalLacunarity(2.1);
    elevNoise.SetFractalGain(0.7);
    ///
    moisNoise.SetNoiseType(FastNoise::SimplexFractal);
    moisNoise.SetSeed(rand());
    moisNoise.SetFrequency(3);
    moisNoise.SetFractalOctaves(3);
    moisNoise.SetFractalType(FastNoise::FBM);
    moisNoise.SetFractalLacunarity(2.0);
    moisNoise.SetFractalGain(0.5);
    ///
    tempNoise.SetNoiseType(FastNoise::SimplexFractal);
    tempNoise.SetSeed(rand());
    tempNoise.SetFrequency(5);
    tempNoise.SetFractalOctaves(10);
    tempNoise.SetFractalType(FastNoise::FBM);
    tempNoise.SetFractalLacunarity(2.1);
    tempNoise.SetFractalGain(0.5);
}





