//
// Created by lowIQ on 2021-06-17.
//

#include "Map.h"
#include "TextureManager.h"
#include <fstream>

Map::Map()
{

}

Map::~Map()
{

}

void Map::LoadMap(std::string path, int sizeX, int sizeY)
{
    char tile;

        std::fstream mapFile(path);

        for (int y = 0; y < sizeY; y++) {
            for (int x = 0; x < sizeX; x++) {
                mapFile >> tile;
                Game::AddTile(atoi(&tile), x * 32, y * 32);
                mapFile.ignore();
            }
        }

}


