//
// Created by acurr on 12/1/2017.
//

#ifndef DUNGEON_WORLDGENERATOR_H
#define DUNGEON_WORLDGENERATOR_H


#include <vector>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Thread.hpp>
#include "FastNoise.h"

class WorldGenerator {
    double size;
public:

	/**
	* Struct which contains the random generation parameters used for noise generation
	* Used to assist with display of the parameters and changing the params based on user input
	*/
	struct noiseSetting {
		double freq;
		double oct;
		double lac;
		double gain;
	};

	noiseSetting elev;
	noiseSetting moist;
	noiseSetting temp;

    explicit WorldGenerator(int size);
    WorldGenerator();
    void Render(sf::RenderWindow *window);
    void createGraphics();
    void createNewGraphics();
    void MoveGraphics(float x, float y);


    sf::Color Biome(double e, double m, double t);
private:
    double getNoiseElevation(int x, int y);
    double getNoiseTempature(int x, int y);
    double getNoise_Moisture(int x, int y);
	void setDefaultNoises();
	void setUpNoises();

    std::vector<sf::Texture *> textures;
    std::vector<sf::Sprite *> sprites;
    FastNoise moisNoise;
    FastNoise tempNoise;
    FastNoise elevNoise;
    int lastCreatedx = 0;
    int lastCreatedy = 0;
};


#endif //DUNGEON_WORLDGENERATOR_H
