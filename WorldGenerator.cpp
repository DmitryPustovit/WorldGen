//
// Created by acurr on 12/1/2017.
//

#include <ctime>
#include <SFML/Graphics/RenderWindow.hpp>
#include "WorldGenerator.h"
#include <cmath>

/**
* Creates default 800 x 800 sized world
* Sets up noise
*/
WorldGenerator::WorldGenerator() {
    this->size = 800;
    srand(static_cast<unsigned int>(time(nullptr)));;
	setDefaultNoises();
    setUpNoises();
}

/**
* Creates world based on inputed size
* Sets up noise
*/
WorldGenerator::WorldGenerator(int size) {
    this->size = size;
    srand(static_cast<unsigned int>(time(nullptr)));
	setDefaultNoises();
    setUpNoises();
}

/**
* Creates world based on inputed size and ignores default noise values
* Sets up noise
*/
WorldGenerator::WorldGenerator(int size, bool use) {
	this->size = size;
	srand(static_cast<unsigned int>(time(nullptr)));
	if (use)
	{
		setDefaultNoises();
		setUpNoises();
	}
}

/**
* Renders the world map via the user's current position in relation to the window
*
* @param window
*
* @return none
*/
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

/**
* Move the graphic, in this case terrain, based on input parameters
*
* @param x
* @param y
*
* @return none
*/
void WorldGenerator::MoveGraphics(float x, float y) {
	for (auto sprit : sprites) {
		sprit->move(x, y);
	}
	lastCreatedx += x;
	lastCreatedy += y;
}

/**
* Creates the 16x16 chunck based world map that is then displayed 
* Uses both texture and sprite array for such creation
* @param none
*
* @return none
*/
void WorldGenerator::createGraphics() {
	textures.clear();
	sprites.clear();
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

//Sets the default values for noises, used for the random generation 
void WorldGenerator::setDefaultNoises()
{
	elev.freq = 5;
	elev.oct = 10;
	elev.lac = 2.1;
	elev.gain = 0.7;
	elev.type = "s";

	moist.freq = 3;
	moist.oct = 3;
	moist.lac = 2.0;
	moist.gain = 0.5;
	moist.type = "s";

	temp.freq = 5;
	temp.oct = 10;
	temp.lac = 2.1;
	temp.gain = 0.5;
	temp.type = "s";
}

//Gets elevation of a point
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

//Gets temp of a point
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

//Gets moisture of a point
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

//Thresholds for various created biomes
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

/**
* Creates noise based on parameters
* @param none
*
* @return none
*/
void WorldGenerator::setUpNoises() {
	if (elev.type == "s")
	{
		elevNoise.SetNoiseType(FastNoise::SimplexFractal);
		moisNoise.SetNoiseType(FastNoise::SimplexFractal);
		tempNoise.SetNoiseType(FastNoise::SimplexFractal);
	}
	else if (elev.type == "p")
	{
		elevNoise.SetNoiseType(FastNoise::PerlinFractal);
		moisNoise.SetNoiseType(FastNoise::PerlinFractal);
		tempNoise.SetNoiseType(FastNoise::PerlinFractal);
	}
	else if (elev.type == "c")
	{
		elevNoise.SetNoiseType(FastNoise::CubicFractal);
		moisNoise.SetNoiseType(FastNoise::CubicFractal);
		tempNoise.SetNoiseType(FastNoise::CubicFractal);
	}
	else if (elev.type == "e")
	{
		elevNoise.SetNoiseType(FastNoise::Cellular);
		moisNoise.SetNoiseType(FastNoise::Cellular);
		tempNoise.SetNoiseType(FastNoise::Cellular);
	}
	else if (elev.type == "v")
	{
		elevNoise.SetNoiseType(FastNoise::ValueFractal);
		moisNoise.SetNoiseType(FastNoise::ValueFractal);
		tempNoise.SetNoiseType(FastNoise::ValueFractal);
	}
	else if (elev.type == "w")
	{
		elevNoise.SetNoiseType(FastNoise::WhiteNoise);
		moisNoise.SetNoiseType(FastNoise::WhiteNoise);
		tempNoise.SetNoiseType(FastNoise::WhiteNoise);
	}
	else {
		elevNoise.SetNoiseType(FastNoise::SimplexFractal);
		moisNoise.SetNoiseType(FastNoise::SimplexFractal);
		tempNoise.SetNoiseType(FastNoise::SimplexFractal);
	}


	if (elev.type == "b")
	{
		tempNoise.SetFractalType(FastNoise::Billow);
		tempNoise.SetFractalType(FastNoise::Billow);
		tempNoise.SetFractalType(FastNoise::Billow);
	}
	if (elev.type == "r")
	{
		tempNoise.SetFractalType(FastNoise::RigidMulti);
		tempNoise.SetFractalType(FastNoise::RigidMulti);
		tempNoise.SetFractalType(FastNoise::RigidMulti);
	}
	else {
		elevNoise.SetFractalType(FastNoise::FBM);
		moisNoise.SetFractalType(FastNoise::FBM);
		tempNoise.SetFractalType(FastNoise::FBM);
	}


    ///
	
    elevNoise.SetSeed(rand());
    elevNoise.SetFrequency(elev.freq);
    elevNoise.SetFractalOctaves(elev.oct);
    elevNoise.SetFractalLacunarity(elev.lac);
    elevNoise.SetFractalGain(elev.gain);
    ///
    
    moisNoise.SetSeed(rand());
    moisNoise.SetFrequency(moist.freq);
    moisNoise.SetFractalOctaves(moist.oct);
    moisNoise.SetFractalLacunarity(moist.lac);
    moisNoise.SetFractalGain(moist.gain);
    ///
   
    tempNoise.SetSeed(rand());
    tempNoise.SetFrequency(temp.freq);
    tempNoise.SetFractalOctaves(temp.oct);
    tempNoise.SetFractalLacunarity(temp.lac);
    tempNoise.SetFractalGain(temp.gain);
}



