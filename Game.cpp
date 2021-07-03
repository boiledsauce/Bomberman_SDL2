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

Manager manager;
SDL_Event Game::s_event;


//auto& player(manager.addEntity());
auto& wall(manager.addEntity());

auto& tile0(manager.addEntity());
auto& tile1(manager.addEntity());
auto& tile2(manager.addEntity());


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

auto& tiles(manager.getGroup(groupMap));
auto& players(manager.getGroup(groupPlayers));
auto& enemies(manager.getGroup(groupEnemies));
auto& colliders(manager.getGroup(groupColliders));
auto& bombs(manager.getGroup(groupBombs));

void Game::update()
{



    Vector2D oldPos = player.getComponent<TransformComponent>().m_position;
    SDL_Rect oldCollision = player.getComponent<ColliderComponent>().collider;

    manager.refresh();
    manager.update();

    for (auto &bomb : bombs)
    {
        BombComponent* bombComponent = &bomb->getComponent<BombComponent>();
        int bombTimer = bombComponent->m_bombTimer;

        if (SDL_GetTicks() > bombComponent->m_bombTimer)
        {
            std::cout << "Exploding" << std::endl;
            bombComponent->m_entity->destroy();
        }
    }

for (auto &player : players)
{
    for (auto &collider : colliders)
    {
        ColliderComponent* cc = &collider->getComponent<ColliderComponent>();

        if (Collision::AABB(player->getComponent<ColliderComponent>(), *cc))
        {

            if (cc->m_tag == "bomb")
            {
                Vector2D playerPos = player->getComponent<TransformComponent>().m_position;
                Vector2D bombPos = cc->m_transform->m_position;

                // if your oldPos was on the bomb you placed, let yourself escape it
                SDL_Rect old = {static_cast<int>(oldPos.x), static_cast<int>(oldPos.y), 32, 32};
                if (Collision::AABB(old, cc->collider, "player", "bomb"))
                    continue;
            }
            player->getComponent<KeyboardController>().m_transform->m_position = oldPos;
        }

    }

    CreatureAttributeComponent* playerAttributes = &player->getComponent<CreatureAttributeComponent>();
    TileComponent* currentTile = &player->getComponent<TileComponent>();
    playerAttributes->m_health -= 100;
}




}



void Game::render()
{
    SDL_RenderClear(s_renderer);
    for (auto& t : tiles)
    {
        t->draw();
    }

    for (auto& p : players)
    {
        p->draw();
    }

    for (auto &b : bombs)
    {
        b->draw();
    }

    for (auto& e : enemies)
    {
        e->draw();
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

void Game::AddTile(int id, int x, int y)
{
    auto& tile(manager.addEntity());
    tile.addComponent<TileComponent>(x, y, SPRITE_SIZE, SPRITE_SIZE, id);
    if (id == 0)
    {
        tile.addComponent<ColliderComponent>("block");
        tile.addGroup(groupColliders);
    }

    tile.addGroup(groupMap);
}

void Game::AddBomb(int x, int y, int timer, int damage, int radiusX, int radiusY)
{

    auto &bomb(manager.addEntity());
    int middleXofRect = ((x+16)/32)*32;
    int middleYofRect = ((y+16)/32)*32;

    x = middleXofRect;
    y = middleYofRect;

    bomb.addComponent<TransformComponent>(x,y);
    bomb.addComponent<BombComponent>(timer, damage);
    std::cout << "timer: " << timer << std::endl;
/*    bomb.addComponent<SpriteComponent>("Sprites/bomb.png");
    bomb.addComponent<ColliderComponent>("bomb");*/

    bomb.addGroup(groupBombs);
}
