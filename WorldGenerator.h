//
// Created by acurr on 12/1/2017.
//

#ifndef DUNGEON_WORLDGENERATOR_H
#define DUNGEON_WORLDGENERATOR_H


#include <vector>
#include <SFML/Graphics/RectangleShape.hpp>

class WorldGenerator {
    double size;
    int transitionSize;
public:
    explicit WorldGenerator(int size);
    WorldGenerator(int size, int trans);

    WorldGenerator();
    void CreateMatrix();

    //void Interpolate();
    void Render(sf::RenderWindow *window);
    void createGraphics();

    sf::Color Biome(double e, double m);
private:
    double **_Elevation;
    double **_Moisture;
    std::vector<sf::RectangleShape*> _Graphics;



};


#endif //DUNGEON_WORLDGENERATOR_H
