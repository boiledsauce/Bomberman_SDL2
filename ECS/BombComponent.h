//
// Created by lowIQ on 2021-06-27.
//

#ifndef BOMBERMAN_BOMBCOMPONENT_H
#define BOMBERMAN_BOMBCOMPONENT_H

#include "ECS.h"
#include "Components.h"
#include "../Game.h"



class BombComponent : public Component
{
public:
    bool m_shouldExplode = false;
    int m_bombTimer = 3000;
    int m_damage = 100;
    int m_radiusX = 3;
    int m_radiusY = 3;
    int *bombAmount = nullptr;
    std::vector<std::pair<int,int>> m_explodingTiles;

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
    }

    void explode()
    {
        if (SDL_GetTicks() > m_bombTimer)
        {
            m_shouldExplode = true;
            addExplodingTiles();

            for (auto &itr : m_explodingTiles)
            {
                    auto &tile = Game::s_tiles[std::make_pair(itr.first, itr.second)];

                    if (tile->m_entity->hasComponent<BlockComponent>())
                {
                        tile->m_entity->removeComponent<BlockComponent>();
                        tile->m_entity->removeGroup(groupColliders);
                        tile->m_entity->removeGroup(groupMap);
                        Game::AddReward(tile->m_transform->m_position.Normalize(tile->m_transform->m_position.x), tile->m_transform->m_position.Normalize(tile->m_transform->m_position.y));

                }
                  BombComponent* bomb = Game::Bomb(itr.first, itr.second);
                if (bomb && (bomb->m_entity->entityID() != this->m_entity->entityID()))
                {
                    bomb->m_bombTimer = 0;
                }
            }
            if (bombAmount)
                *bombAmount += 1;

            m_entity->destroy();
        }
    }

    BombComponent(int timer, int damage, int radiusX, int radiusY, int *bombAmount)
    {
        m_bombTimer = timer * 1000 + SDL_GetTicks();
        m_damage = damage;
        m_radiusX = radiusX;
        m_radiusY = radiusY;
        this->bombAmount = bombAmount;
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

//    void draw() override
//    {
//        auto &spriteComponent = m_entity->getComponent<SpriteComponent>();
//
//        for (auto &itr : m_explodingTiles)
//        {
//            SDL_Rect destRect = { itr.first, itr.second, 32, 32 };
//            auto srcRect = spriteComponent.getsrcRect();
//            TextureManager::Draw(m_entity->getComponent<SpriteComponent>().getTexture(), srcRect, destRect, SDL_FLIP_NONE);
//        }
//
//    }

};

#endif //BOMBERMAN_BOMBCOMPONENT_H
