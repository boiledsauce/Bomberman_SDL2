//
// Created by lowIQ on 2021-06-16.
//

#ifndef SDL_PROJ_GAME_H
#define SDL_PROJ_GAME_H

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <vector>
#include <map>

class TileComponent;
class ColliderComponent;

enum groupLabels : std::size_t
{
    groupMap,
    groupPlayers,
    groupEnemies,
    groupColliders,
    groupBombs
};


class Game {
public:
    Game();
    ~Game();

    void init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen);

    void handleEvents();
    void update();
    void render();
    void clean();

    inline bool running() const { return isRunning; }
    static SDL_Renderer* s_renderer;
    static SDL_Event s_event;
    static SDL_Window* s_window;

    static std::vector<ColliderComponent*> s_colliders;
    static std::map<std::pair<int,int>, TileComponent*> s_tiles;

    static void AddTile(int id, int x, int y);
    static void AddBomb(int x, int y, int timer, int damage, int radX, int radY);

private:
    int m_updateCounter;
    bool isRunning;
};


#endif //SDL_PROJ_GAME_H
