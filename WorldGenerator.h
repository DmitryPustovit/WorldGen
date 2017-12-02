//
// Created by acurr on 12/1/2017.
//

#ifndef DUNGEON_WORLDGENERATOR_H
#define DUNGEON_WORLDGENERATOR_H


#include <vector>
#include <SFML/Graphics/RectangleShape.hpp>

class WorldGenerator {
    int size;
    int transitionSize;
public:
    explicit WorldGenerator(int size);
    WorldGenerator(int size, int trans);
    void CreateMatrix();
    void Interpolate();
    void Render(sf::RenderWindow *window);
    void createGraphics();
private:
    int** _Matrix;
    std::vector<sf::RectangleShape*> _Graphics;



};


#endif //DUNGEON_WORLDGENERATOR_H
