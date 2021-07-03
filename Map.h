//
// Created by lowIQ on 2021-06-17.
//

#ifndef BOMBERMAN_MAP_H
#define BOMBERMAN_MAP_H
#include "Game.h"
#include <vector>
#include <string>

class Map {
public:

    Map();
    ~Map();

    static void LoadMap(std::string path, int sizeX, int sizeY);

private:

};


#endif //BOMBERMAN_MAP_H
