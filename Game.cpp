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
#include "ECS/RewardComponent.h"

//#include <boost/asio.hpp>
//#include <boost/filesystem.hpp>

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
    isRunning = false;
    int windowFlags = SDL_WINDOW_RESIZABLE | static_cast<int>(fullscreen);

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
                    SDL_SetRenderDrawColor(s_renderer, 255, 255, 255, 255);
                    std::cout << "Renderer created!" << std::endl;
                }
                if (TTF_Init() > -1)
                    std::cout << "SDL_TTF text initialized" << std::endl;

                playerCount = Game::mainMenuScreen();
    }
    map = new Map();
    //ecs implementation
    Map::LoadMap("Sprites/bomberman.txt", 25, 25);

    std::array<std::pair<int,int>, 4> startPos = {std::make_pair(1*32, 1*32), std::make_pair(1*32, 23*32), std::make_pair(23*32, 1*32), std::make_pair(23*32, 23*32) };
    std::array<std::array<SDL_KeyCode, 5>, 4> controllers = {{
            {SDLK_UP, SDLK_DOWN, SDLK_RIGHT, SDLK_LEFT, SDLK_SPACE},
            {SDLK_w, SDLK_s, SDLK_d, SDLK_a, SDLK_TAB},
            {SDLK_KP_8, SDLK_KP_5, SDLK_KP_6, SDLK_KP_4, SDLK_KP_0},
            {SDLK_UP, SDLK_DOWN, SDLK_RIGHT, SDLK_LEFT, SDLK_SPACE}
    }};

    std::cout << "PALYERS: " << playerCount << std::endl;
    for (int i = 0; i < playerCount; i++)
    {
        auto &player = manager.addEntity();
        player.addComponent<CreatureAttributeComponent>();
        player.addComponent<TransformComponent>(startPos[i].first, startPos[i].second, 32, 32, 1);
        std::string spritePath = "Sprites/chararcter/player" + std::to_string(i+1) + ".png";
        player.addComponent<SpriteComponent>(spritePath.c_str(), true);
        player.addComponent<KeyboardController>(controllers[i][0], controllers[i][1], controllers[i][2], controllers[i][3], controllers[i][4]);
        player.addComponent<ColliderComponent>("player");
        player.addGroup(groupPlayers);
    }
}

int Game::mainMenuScreen()
{
    int playerAmount = 0;

    enum buttonTypes {NO_BUTTON, GAME_START, GAME_ADD_PLAYER, GAME_PLAYERNAME, GAME_REMOVE_PLAYER};

    struct Graphic
            {
                SDL_Texture* visual;
                buttonTypes buttonType;
                SDL_Rect dimensions;
                SDL_Rect destination;

                bool isClicked(int mouseXPos, int mouseYPos)
                {
                    SDL_Rect mousePos = {mouseXPos, mouseYPos, 0, 0};
                    bool isInside =
                    Collision::AABB(destination, mousePos, "button", "mouse");

                    return isInside;
                }
            };

    std::vector<Graphic> graphicObjects;
    SDL_Texture* MainScreen = TextureManager::LoadTexture("Sprites/MainMenu/background.png");
    SDL_Texture* playButton = TextureManager::LoadTexture("Sprites/MainMenu/play.png");
    SDL_Texture* addPlayer = TextureManager::LoadTexture("Sprites/Mainmenu/addplayer.png");
    SDL_Texture* removePlayer = TextureManager::LoadTexture("Sprites/Mainmenu/removeplayer.png");
    SDL_Texture* fontHeadLine = TextureManager::LoadTTF_Texture("Verdana", 50, "Welcome to bomberman", {255,255,255});

    SDL_Texture* p1 = TextureManager::LoadTTF_Texture("Verdana", 10, "Player1", {0,0,255});
    SDL_Texture* p2 = TextureManager::LoadTTF_Texture("Verdana", 10, "Player2", {255,0,0});
    SDL_Texture* p3 = TextureManager::LoadTTF_Texture("Verdana", 10, "Player3", {127,0,255});
    SDL_Texture* p4 = TextureManager::LoadTTF_Texture("Verdana", 10, "Player4", {50,255,255});

    std::array<std::array<SDL_Texture*,2>, 4> players =
            {
                    { {TextureManager::LoadTexture("Sprites/chararcter/player1.png"), p1},
                            {TextureManager::LoadTexture("Sprites/chararcter/player2.png"), p2},
                            {TextureManager::LoadTexture("Sprites/chararcter/player3.png"), p3},
                            {TextureManager::LoadTexture("Sprites/chararcter/player4.png"), p4}
                            }
            };


    graphicObjects.push_back({MainScreen, NO_BUTTON, {0,0,800,800}, {0,0,800,800}});
    graphicObjects.push_back({playButton, GAME_START, {0,0,400,200}, {200,500,400,150}});
    graphicObjects.push_back({fontHeadLine, NO_BUTTON, TextureManager::FontNullRect, {150,60,500,100}});
    graphicObjects.push_back({addPlayer, GAME_ADD_PLAYER, {0,0,100,100}, {200,200,100,100}});
    graphicObjects.push_back({removePlayer, GAME_REMOVE_PLAYER, {0,0,100,100}, {500,200,100,100}});

    SDL_Rect* currentTextInputButton = nullptr;

    while (! Game::isRunning ) {

        SDL_PollEvent(&s_event);

        switch (s_event.type) {
            case SDL_QUIT:
                isRunning = false;

            case SDL_TEXTINPUT:
                if (currentTextInputButton)
                {

                }
                break;
            case SDL_MOUSEBUTTONDOWN:
            {
                int mouseXPos;
                int mouseYPos;
                SDL_GetMouseState(&mouseXPos, &mouseYPos);

                for (auto &graphicObject : graphicObjects)
                {

                    if (graphicObject.isClicked(mouseXPos, mouseYPos) && graphicObject.buttonType)
                    {
                        SDL_SetTextureAlphaMod(graphicObject.visual, 100);
                        std::cout << mouseXPos << " " << mouseYPos << std::endl;
                        SDL_SetTextureAlphaMod(graphicObject.visual, 255);

                        switch (graphicObject.buttonType)
                        {
                            case GAME_START:
                                std::cout << "Starting game " << std::endl;
                                SDL_Delay(50);
                                Game::isRunning = true;
                                break;

                            case GAME_ADD_PLAYER:
                                if (playerAmount < 4)
                                {
                                    graphicObjects.push_back({players[playerAmount][0], NO_BUTTON, {0, 0, 32, 32},{125 + (playerAmount * 150), 400, 80, 80}});
                                    graphicObjects.push_back({players[playerAmount][1], NO_BUTTON, TextureManager::FontNullRect,{125 + (playerAmount * 150), 300, 120, 90}});

                                    playerAmount += 1;
                                    SDL_Delay(150);
                                }
                                break;

                            case GAME_REMOVE_PLAYER:
                            {
                                if (playerAmount > 0) {
                                    std::cout << "Pl: " << playerAmount << std::endl;
                                    graphicObjects.erase(std::remove_if(graphicObjects.begin(), graphicObjects.end(),[&](Graphic curObj)
                                                                        {
                                                                            bool ok = curObj.visual == players[playerAmount-1][0] || curObj.visual == players[playerAmount-1][1];
                                                                            return ok;
                                                                        }), graphicObjects.end());
                                    playerAmount -= 1;
                                    SDL_Delay(150);
                                }
                                break;
                            }
                            case GAME_PLAYERNAME:
                                currentTextInputButton = &graphicObject.dimensions;
                                break;

                            default:
                                break;
                        }
                    }
                }


            }
                break;

            default:
                break;
        }

        for (auto &graphicObject : graphicObjects)
        {
            auto &texture = graphicObject.visual;
            {
                TextureManager::Draw(texture, graphicObject.dimensions, graphicObject.destination, SDL_FLIP_NONE);
            }
        }
        SDL_RenderPresent(Game::s_renderer);
    }

    return playerAmount;
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
    if (!Game::isRunning)
    {
        return;
    }

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

    for (auto &reward : manager.getGroup(groupRewards))
    {
        auto &creatureAttributeComponent = player->getComponent<CreatureAttributeComponent>();
        auto &rewardComponent = reward->getComponent<RewardComponent>();

        SDL_Rect position = {middleXofRect, middleYofRect, 32, 32};
        SDL_Rect rewardPos = {static_cast<int>(rewardComponent.m_transform->m_position.x), static_cast<int>(rewardComponent.m_transform->m_position.y), 32, 32};

        if (Collision::AABB(position, rewardPos, "", ""))
        {
            switch (rewardComponent.m_powerUp)
            {
                case SPEED_PLAYER:
                    playerTransform.m_speed += 0.2;
                    break;

                case DAMAGE:
                    playerAttributes->m_explosionDamage += 25;
                    break;

                case RADIUS:
                    std::cout << playerAttributes->m_explosionRadiusX << " RadX" << std::endl;
                    playerAttributes->m_explosionRadiusX += 1;
                    playerAttributes->m_explosionRadiusY += 1;
                    std::cout << playerAttributes->m_explosionRadiusX << "RadX #2 " << std::endl;
                    break;

                case SPEED_BOMB:
                    playerAttributes->m_bombTimer -= 0.2;
                    break;

                case EXTRA_BOMB:
                    playerAttributes->m_bombAmount += 1;
                    break;

                default:
                    break;
            }
            reward->destroy();
        }
    }

//    auto &tile = Game::s_tiles[std::make_pair(x,y)];
//    std::cout << tile->m_damage << " " << playerAttributes->m_health << " :" << std::endl;
//    playerAttributes->m_health -= tile->m_damage;
}




}


void Game::render()
{
    SDL_RenderClear(s_renderer);

    if (! Game::isRunning )
    {
        return;
    }

    for (auto& t : Game::manager.getGroup(groupMap))
    {
        t->draw();
    }

    for (auto& e : Game::manager.getGroup(groupExplosions))
    {
        e->draw();
    }

    for (auto &r : Game::manager.getGroup(groupRewards))
    {
        r->draw();
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

bool Game::isStartPos(int x, int y)
{
    return true;
}

void Game::AddTile(int id, int x, int y)
{
    auto& tile(manager.addEntity());
    tile.addComponent<TileComponent>(x, y, SPRITE_SIZE, SPRITE_SIZE, id);
    int add = SDL_GetTicks()%1;

    if (x == 1*32 && y == 1*32 || x == 1*32 && y == 23*32 || x == 23*32 && y == 1*32 || x == 23*32 && y == 23*32)
        return;

    if (id == 0)
    {
        tile.addComponent<ColliderComponent>("block");
        tile.addGroup(groupColliders);
    }
    else if (id == 2) {
        if (add)
        {
            tile.addComponent<BlockComponent>(x, y);
            tile.addComponent<ColliderComponent>("block");
            tile.addGroup(groupColliders );
        }
    }


    tile.addGroup(groupMap);

}

void Game::AddBomb(int x, int y, int timer, int damage, int radiusX, int radiusY, int* bombAmount)
{

    auto &bomb(manager.addEntity());
    int middleXofRect = ((x+16)/32)*32;
    int middleYofRect = ((y+16)/32)*32;

    std::cout << middleXofRect << " " << middleYofRect << std::endl;
    x = middleXofRect;
    y = middleYofRect;

    bomb.addComponent<TransformComponent>(x,y);
    bomb.addComponent<BombComponent>(timer, damage, radiusX, radiusY, bombAmount);
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

void Game::AddReward(int x, int y)
{
    auto &reward(Game::manager.addEntity());
    reward.addComponent<RewardComponent>(x,y);
    reward.addGroup(groupRewards);
}
