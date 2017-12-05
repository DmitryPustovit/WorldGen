//
// Created by acurr on 12/1/2017.
//

#ifndef DUNGEON_WORLDGENERATOR_H
#define DUNGEON_WORLDGENERATOR_H


#include <vector>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "FastNoise.h"

class WorldGenerator {
    double size;
public:
    explicit WorldGenerator(int size);

    WorldGenerator();

    void Render(sf::RenderWindow *window);
    void createGraphics();

    void MoveGraphics(float x, float y);

    sf::Color Biome(double e, double m);
private:
    double getNoiseElevation(int x, int y);

    double getNoise_Moisture(int x, int y);

    void setUpNoises();

    std::vector<sf::Texture *> textures;
    std::vector<sf::Sprite *> sprites;
    FastNoise moisNoise;
    FastNoise elevNoise;



};


#endif //DUNGEON_WORLDGENERATOR_H
