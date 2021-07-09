//
// Created by lowIQ on 2021-06-16.
//

#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "Constants.h"
#include "ECS/BombComponent.h"
#include "ECS/TileComponent.h"

SDL_Window* Game::s_window = nullptr;
SDL_Renderer* Game::s_renderer = nullptr;
Map* map;

Manager Game::manager;
SDL_Event Game::s_event;


//auto& player(manager.addEntity());


std::map<std::pair<int,int>, TileComponent*> Game::s_tiles;
std::vector<ColliderComponent*> Game::s_colliders;

Game::Game()
{
    s_window = nullptr;
    m_updateCounter = 0;
}

Game::~Game()
{
    clean();
}

void Game::init(const char *title, int xPos, int yPos, int width, int height, bool fullscreen)
{
    int windowFlags = SDL_WINDOW_RESIZABLE | static_cast<int>(fullscreen);
 /* if(fullscreen)
    {
        windowFlags = SDL_WINDOW_FULLSCREEN;
    }*/

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "Subsystems initialized" << std::endl;
        s_window = SDL_CreateWindow(title, xPos, yPos, width, height, windowFlags);
                if (s_window)
                {
                    std::cout << "Window created " << std::endl;
                }

                s_renderer = SDL_CreateRenderer(s_window, -1, SDL_RENDERER_ACCELERATED);
                if (s_renderer)
                {
                    //SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
                    SDL_SetRenderDrawColor(s_renderer, 255, 255, 255, 255);
                    std::cout << "Renderer created!" << std::endl;
                }
                isRunning = true;
    }
    map = new Map();
    //ecs implementation
    Map::LoadMap("Sprites/bomberman.txt", 25, 25);


    auto &player = (manager.addEntity());
    player.addComponent<TransformComponent>(400,400,32,32,1);
    player.addComponent<SpriteComponent>("Sprites/chararcter/player.png", true);
    player.addComponent<KeyboardController>();
    player.addComponent<ColliderComponent>("player");
    player.addComponent<CreatureAttributeComponent>();
    player.addGroup(groupPlayers);




}

void Game::handleEvents()
{
    SDL_PollEvent(&s_event);

    switch(s_event.type)
    {
        case SDL_QUIT:
            isRunning = false;
            break;

        default:
            break;
    }
}

auto& tiles(Game::manager.getGroup(groupMap));
auto& players(Game::manager.getGroup(groupPlayers));
auto& enemies(Game::manager.getGroup(groupEnemies));
auto& colliders(Game::manager.getGroup(groupColliders));
auto& bombs(Game::manager.getGroup(groupBombs));
auto& explosions(Game::manager.getGroup(groupExplosions));

void Game::update()
{
    std::map<int, std::pair<Vector2D, SDL_Rect>> previousPlayerValues;

    for (auto &player : players)
    {

            Vector2D playerPos = player->getComponent<TransformComponent>().m_position;
            SDL_Rect playerCollider = player->getComponent<ColliderComponent>().collider;

            previousPlayerValues.insert(std::make_pair(player->entityID(), std::make_pair(playerPos, playerCollider)));
    }


    manager.refresh();
    manager.update();


    for (auto &bomb : bombs)
    {
        auto& bombComponent = bomb->getComponent<BombComponent>();
        if (bombComponent.m_shouldExplode)
        {
            auto &bombTiles = bombComponent.m_explodingTiles;
            for (int i = 0; i < bombComponent.m_explodingTiles.size(); i++)
            {
                Game::AddExplosion(bombTiles[i].first, bombTiles[i].second, bombComponent.m_damage, 1000);
            }
            bomb->destroy();
        }
    }

for (auto &player : manager.getGroup(groupPlayers))
{
    for (auto &collider : manager.getGroup(groupColliders))
    {
        ColliderComponent* cc = &collider->getComponent<ColliderComponent>();

        if (Collision::AABB(player->getComponent<ColliderComponent>(), *cc))
        {
            if (cc->m_tag == "bomb")
            {
                Vector2D playerPos = player->getComponent<TransformComponent>().m_position;
                Vector2D bombPos = cc->m_transform->m_position;

                // if your oldPos was on the bomb you placed, let yourself escape it
                SDL_Rect old = {static_cast<int>(previousPlayerValues[player->entityID()].first.x),
                                static_cast<int>(previousPlayerValues[player->entityID()].first.y),
                                32,
                                32};

                if (Collision::AABB(old, cc->collider, "player", "bomb"))
                    continue;
            }
       /*     std::cout << "PosBefore:" << previousPlayerValues[player->entityID()].first << std::endl;
            std::cout << "PosNow:" << player->getComponent<TransformComponent>().m_position << std::endl;
*/
            player->getComponent<TransformComponent>().m_position = previousPlayerValues[player->entityID()].first;
        }

    }

    CreatureAttributeComponent* playerAttributes = &player->getComponent<CreatureAttributeComponent>();
    auto& playerTransform = player->getComponent<TransformComponent>();
    int middleXofRect = ((playerTransform.m_position.x + 16) / 32) * 32;
    int middleYofRect = ((playerTransform.m_position.y + 16) / 32) * 32;

    int x = ((static_cast<int>(playerTransform.m_position.x) + 16) / 32) * 32;
    int y = ((static_cast<int>(playerTransform.m_position.y) + 16) / 32) * 32;

    for (auto &explosion : manager.getGroup(groupExplosions))
    {
        auto &tile = Game::s_tiles[std::make_pair(x,y)];
        auto &explosionPos = explosion->getComponent<TransformComponent>().m_position;
        auto &explosionPosX = explosionPos.x;
        auto &explosionPosY = explosionPos.y;

        if ( x ==  explosionPosX && y == explosionPosY)
            playerAttributes->m_health -= explosion->getComponent<ExplosionComponent>().m_damage;
    }
//    auto &tile = Game::s_tiles[std::make_pair(x,y)];
//    std::cout << tile->m_damage << " " << playerAttributes->m_health << " :" << std::endl;
//    playerAttributes->m_health -= tile->m_damage;
}




}


void Game::render()
{
    SDL_RenderClear(s_renderer);

    for (auto& t : Game::manager.getGroup(groupMap))
    {
        t->draw();
    }

    for (auto& e : Game::manager.getGroup(groupExplosions))
    {
        e->draw();
    }

    for (auto& p : Game::manager.getGroup(groupPlayers))
    {
        p->draw();
    }

    for (auto &b : Game::manager.getGroup(groupBombs))
    {
        b->draw();
    }

    for (auto& en : Game::manager.getGroup(groupEnemies))
    {
        en->draw();
    }

    SDL_RenderPresent(s_renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(s_window);
    SDL_DestroyRenderer(s_renderer);
    SDL_Quit(); // subsystems
    std::cout << "Game cleaned" << std::endl;
}

void Game::AddBlock(int x, int y)
{
//    auto& block(manager.addEntity());
//    block.addComponent<BlockComponent>(x,y);
//    block.addGroup(groupColliders);

}

void Game::AddTile(int id, int x, int y)
{
    auto& tile(manager.addEntity());
    tile.addComponent<TileComponent>(x, y, SPRITE_SIZE, SPRITE_SIZE, id);
    int add = SDL_GetTicks()%5;

    if (id == 0)
    {
        tile.addComponent<ColliderComponent>("block");
        tile.addGroup(groupColliders);
    }
    else if (id == 2) {
        if (add) {
            tile.addComponent<BlockComponent>(x, y);
            tile.addComponent<ColliderComponent>("block");
            tile.addGroup(groupColliders );
        }
    }


    tile.addGroup(groupMap);

}

void Game::AddBomb(int x, int y, int timer, int damage, int radiusX, int radiusY)
{

    auto &bomb(manager.addEntity());
    int middleXofRect = ((x+16)/32)*32;
    int middleYofRect = ((y+16)/32)*32;

    std::cout << middleXofRect << " " << middleYofRect << std::endl;
    x = middleXofRect;
    y = middleYofRect;

    bomb.addComponent<TransformComponent>(x,y);
    bomb.addComponent<BombComponent>(timer, damage, radiusX, radiusY);
}

void Game::AddExplosion(int x, int y, int damage, int duration)
{
    auto &explosion(Game::manager.addEntity());
    explosion.addComponent<ExplosionComponent>(x, y, damage, duration);
    explosion.addGroup(groupExplosions);
}

//bool Game::hasExplosion(int x, int y)
//{
//    return true || false;
//}

BombComponent* Game::Bomb(int x, int y)
{
    for (auto &bomb : bombs)
    {
        auto &position = bomb->getComponent<TransformComponent>().m_position;
        auto bombPosX = static_cast<int>(position.x);
        auto bombPosY = static_cast<int>(position.y);

        if (x == bombPosX && y == bombPosY)
            return &bomb->getComponent<BombComponent>();
    }

    return nullptr;
}