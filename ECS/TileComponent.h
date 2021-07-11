//
// Created by lowIQ on 2021-06-22.
//

#ifndef BOMBERMAN_TILECOMPONENT_H
#define BOMBERMAN_TILECOMPONENT_H

#include "ECS.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "SDL.h"
#include "Constants.h"
#include "..\Game.h"
#include "BlockComponent.h"
#include "ExplosionComponent.h"
#include "RewardComponent.h"
enum groupLabels : std::size_t;

class TileComponent : public Component
{
public:
    TransformComponent* m_transform;
    SpriteComponent* m_sprite;


    SDL_Rect tileRect;
    int m_tileID;
    const char* m_path;


    TileComponent() = default;
    TileComponent(int x, int y, int w, int h, int id)
    {
        tileRect.x = x;
        tileRect.y = y;
        tileRect.w = w;
        tileRect.h = h;
        m_tileID = id;

        Game::s_tiles.insert(std::make_pair(std::make_pair(tileRect.x, tileRect.y),this));

        switch(m_tileID)
        {
            case 0:
                m_path = "Sprites/black.png";
                break;

            case 1:
                m_path = "Sprites/water.png";
                break;

            case 2:
                m_path = "Sprites/white.png";
                break;

            case 3:
                m_path = "Sprites/bridge.png";
                break;

            case 4:
                m_path = "Sprites/grass.png";
                break;

            default:
                break;
        }
    }

    void init() override
    {
        m_entity->addComponent<TransformComponent>((float) tileRect.x, (float) tileRect.y, (float) tileRect.w, (float) tileRect.h,1);
        m_transform = &m_entity->getComponent<TransformComponent>();
        m_entity->addComponent<SpriteComponent>(m_path);
        m_sprite = &m_entity->getComponent<SpriteComponent>();
    }

    void update() override
    {

    }
};
#endif //BOMBERMAN_TILECOMPONENT_H
