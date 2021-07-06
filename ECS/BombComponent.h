//
// Created by lowIQ on 2021-06-27.
//

#ifndef BOMBERMAN_BOMBCOMPONENT_H
#define BOMBERMAN_BOMBCOMPONENT_H

#include "ECS.h"
#include "Components.h"



class BombComponent : public Component
{
public:
    int m_bombTimer = 3000;
    int m_damage = 100;
    int m_radiusX = 3;
    int m_radiusY = 3;
    std::vector<std::pair<int,int>> m_explodingTiles;
    std::vector<BombComponent> m_neighborBombs;

    void addExplodingTiles()
    {
        m_explodingTiles.clear();

        auto &position = m_entity->getComponent<TransformComponent>().m_position;
        m_explodingTiles.emplace_back(std::make_pair(position.x, position.y));

        std::map<int, bool> disallow_direction;
        for (int i = 32; i <= m_radiusX*32; i+=32)
        {
            std::array<std::pair<float,float>, 4> arr = {{
                                                            {position.x+i, position.y},
                                                            {position.x-i, position.y},
                                                            {position.x,position.y+i},
                                                            {position.x, position.y-i}
                                                                }
                                                        };
            for (int j = 0; j < arr.size(); j++)
            {
                auto &tile = Game::s_tiles[std::make_pair(arr[j].first, arr[j].second)];

                if (disallow_direction[j])
                    continue;

                if (tile->m_entity->hasGroup(groupColliders))
                {
                    disallow_direction[j] = true;
                }
                    m_explodingTiles.emplace_back(std::make_pair(arr[j].first, arr[j].second));
            }
        }
//        std::cout << "------------------------------------" << std::endl;
//        for (auto i : m_explodingTiles)
//        {
//            std::cout << i.first << " " << i.second << std::endl;
//        }
    }

    void modifyNeighborBombTimer()
    {


    }

    void explode()
    {
        if (SDL_GetTicks() > m_bombTimer)
        {
            addExplodingTiles();
            m_entity->getComponent<SpriteComponent>().setTexture("Sprites/explosion.png");

            std::cout << "Exploding" << std::endl;
            std::cout << "Coordinates" << std::endl;

            for (auto &itr : m_explodingTiles)
            {
                auto &tile = Game::s_tiles[std::make_pair(itr.first,itr.second)];

                if (tile->m_entity->hasComponent<BlockComponent>())
                {
                    tile->m_entity->removeComponent<BlockComponent>();
                    tile->m_entity->removeGroup(groupColliders);
                    tile->m_entity->removeGroup(groupMap);

                }
//                std::cout << "[ " << itr.first << " : " << itr.second << " ]" << std::endl;



                Game::s_tiles[std::make_pair(itr.first, itr.second)]->m_damage = m_damage;
                Game::s_tiles[std::make_pair(itr.first, itr.second)]->m_damageTicks = SDL_GetTicks()+750;

            }

            m_entity->destroy();
        }
    }

    BombComponent(int timer, int damage, int radiusX, int radiusY)
    {
        m_bombTimer = timer * 1000 + SDL_GetTicks();
        m_damage = damage;
        m_radiusX = radiusX;
        m_radiusY = radiusY;

    }

    ~BombComponent()
    {}

    void init() override
    {
        m_entity->addComponent<SpriteComponent>("Sprites/bomb.png");
        m_entity->addComponent<ColliderComponent>("bomb");
        m_entity->addGroup(groupColliders);
        m_entity->addGroup(groupBombs);
    }

    void update() override
    {
        explode();
    }

    void draw() override
    {
        auto &spriteComponent = m_entity->getComponent<SpriteComponent>();

        for (auto &itr : m_explodingTiles)
        {
            SDL_Rect destRect = { itr.first, itr.second, 32, 32 };
            auto srcRect = spriteComponent.getsrcRect();
            TextureManager::Draw(m_entity->getComponent<SpriteComponent>().getTexture(), srcRect, destRect, SDL_FLIP_NONE);
        }

    }

};

#endif //BOMBERMAN_BOMBCOMPONENT_H
