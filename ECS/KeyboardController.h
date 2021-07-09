//
// Created by lowIQ on 2021-06-19.
//

#ifndef BOMBERMAN_KEYBOARDCONTROLLER_H
#define BOMBERMAN_KEYBOARDCONTROLLER_H

#include "..\Game.h"
#include "ECS.h"
#include "Components.h"
#include "CreatureAttributeComponent.h"


class KeyboardController : public Component {
public:
    TransformComponent *m_transform;
    SpriteComponent *m_sprite;
    CreatureAttributeComponent* m_attributes;

//    int m_keyNorth;
//    int m_keySouth;
//    int m_keyLeft;
//    int m_keyRight;
//    int m_keyBomb;



    void init() override
    {
        m_transform = &m_entity->getComponent<TransformComponent>();
        m_sprite = &m_entity->getComponent<SpriteComponent>();
        m_attributes = &m_entity->addComponent<CreatureAttributeComponent>();
    }

    void update() override {
        if (Game::s_event.type == SDL_KEYDOWN) {
            switch (Game::s_event.key.keysym.sym) {
                case SDLK_UP:
                    m_transform->m_velocity.y = -1;
                    m_sprite->Play("Walk");
                    break;

                case SDLK_DOWN:
                    m_transform->m_velocity.y = 1;
                    m_sprite->Play("Walk");
                    break;

                case SDLK_RIGHT:
                    m_transform->m_velocity.x = 1;
                    m_sprite->Play("Walk");
                    break;

                case SDLK_LEFT:
                    m_transform->m_velocity.x = -1;
                    m_sprite->Play("Walk");
                    m_sprite->m_spriteFlip = SDL_FLIP_HORIZONTAL;
                    break;

                case SDLK_SPACE: {
                    int x = m_transform->m_position.Normalize(m_transform->m_position.x);
                    int y = m_transform->m_position.Normalize(m_transform->m_position.y);
                    if (Game::Bomb(x, y) == nullptr) {
                        Game::AddBomb(m_transform->m_position.x, m_transform->m_position.y, m_attributes->m_bombTimer,
                                      m_attributes->m_explosionDamage, m_attributes->m_explosionRadiusX,
                                      m_attributes->m_explosionRadiusY);
                    }
                    break;
                }
                default:
                    break;
            }
        }

        if (Game::s_event.type == SDL_KEYUP) {

            switch (Game::s_event.key.keysym.sym) {
                case SDLK_UP:
                    m_transform->m_velocity.y = 0;
                    m_sprite->Play("Idle");
                    break;

                case SDLK_DOWN:
                    m_transform->m_velocity.y = 0;
                    m_sprite->Play("Idle");
                    break;

                case SDLK_RIGHT:
                    m_transform->m_velocity.x = 0;
                    m_sprite->Play("Idle");
                    break;

                case SDLK_LEFT:
                    m_transform->m_velocity.x = 0;
                    m_sprite->Play("Idle");
                    m_sprite->m_spriteFlip = SDL_FLIP_NONE;
                    break;

                case SDLK_SPACE:
                    break;

                default:
                    //m_sprite->Play("");
                    break;
            }

        }
    }
};

#endif //BOMBERMAN_KEYBOARDCONTROLLER_H