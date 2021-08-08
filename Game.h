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
#include "SDL_ttf.h"
#include "RandomNumber.h"

class TileComponent;
class ColliderComponent;
class BombComponent;
class ExplosionComponent;
class Manager;

enum groupLabels : std::size_t
{
    groupMap,
    groupPlayers,
    groupEnemies,
    groupColliders,
    groupExplosions,
    groupBombs,
    groupRewards
};


class Game {
public:
    Game();
    ~Game();

//    struct player
//    {
//        std::vector<std::string> playerNames;
//        int playerAmount;
//        int botAmount;
//
//    };

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
    static Manager manager;

    static void AddBlock(int x, int y);
    static void AddTile(int id, int x, int y);
    static void AddBomb(int x, int y, int timer, int damage, int radX, int radY, int *bombAmount);
    static void AddExplosion(int x, int y, int damage, int duration);
    static void AddReward(int x, int y);
    bool isStartPos(int x, int y);
    //bool Game::hasExplosion(int x, int y);

    static BombComponent* Bomb(int x, int y);


protected:
    int mainMenuScreen();

private:
    int m_updateCounter;
    bool isRunning;
    int playerCount;
};


#endif //SDL_PROJ_GAME_H
