//
// Created by lowIQ on 2021-06-19.
//

#ifndef BOMBERMAN_KEYBOARDCONTROLLER_H
#define BOMBERMAN_KEYBOARDCONTROLLER_H

#include "..\Game.h"
#include "ECS.h"
#include "Components.h"
#include "CreatureAttributeComponent.h"


struct keyMovement
{
     SDL_KeyCode up;
     SDL_KeyCode down;
     SDL_KeyCode right;
     SDL_KeyCode left;
     SDL_KeyCode bomb;
};

class KeyboardController : public Component {
public:
    TransformComponent *m_transform;
    SpriteComponent *m_sprite;
    CreatureAttributeComponent *m_attributes;
    keyMovement m_keys;

    void init() override {
        m_transform = &m_entity->getComponent<TransformComponent>();
        m_sprite = &m_entity->getComponent<SpriteComponent>();
        m_attributes = &m_entity->addComponent<CreatureAttributeComponent>();
    }

    KeyboardController(SDL_KeyCode up, SDL_KeyCode down, SDL_KeyCode right, SDL_KeyCode left, SDL_KeyCode bomb) {
        m_keys.up = up;
        m_keys.down = down;
        m_keys.right = right;
        m_keys.left = left;
        m_keys.bomb = bomb;
    }


    void update() override {
        if (Game::s_event.type == SDL_KEYDOWN) {
            SDL_KeyCode key = static_cast<SDL_KeyCode>(Game::s_event.key.keysym.sym);

            if (key == m_keys.up) {
                m_transform->m_velocity.y = -1;
                m_sprite->Play("Walk");
            } else if (key == m_keys.down) {
                m_transform->m_velocity.y = 1;
                m_sprite->Play("Walk");
            } else if (key == m_keys.right) {
                m_transform->m_velocity.x = 1;
                m_sprite->Play("Walk");
            } else if (key == m_keys.left) {
                m_transform->m_velocity.x = -1;
                m_sprite->Play("Walk");
                m_sprite->m_spriteFlip = SDL_FLIP_HORIZONTAL;
            } else if (key == m_keys.bomb) {
                int x = m_transform->m_position.Normalize(m_transform->m_position.x);
                int y = m_transform->m_position.Normalize(m_transform->m_position.y);

                if (m_attributes->m_bombAmount > 0 && Game::Bomb(x, y) == nullptr) {
                    m_attributes->m_bombAmount -= 1;
                    Game::AddBomb(m_transform->m_position.x, m_transform->m_position.y, m_attributes->m_bombTimer,
                                  m_attributes->m_explosionDamage, m_attributes->m_explosionRadiusX,
                                  m_attributes->m_explosionRadiusY, &m_attributes->m_bombAmount);
                }
            }

//            switch (Game::s_event.key.keysym.sym) {
//                case SDLK_UP:
//                    m_transform->m_velocity.y = -1;
//                    m_sprite->Play("Walk");
//                    break;
//
//                case SDLK_DOWN:
//                    m_transform->m_velocity.y = 1;
//                    m_sprite->Play("Walk");
//                    break;
//
//                case SDLK_RIGHT:
//                    m_transform->m_velocity.x = 1;
//                    m_sprite->Play("Walk");
//                    break;
//
//                case SDLK_LEFT:
//                    m_transform->m_velocity.x = -1;
//                    m_sprite->Play("Walk");
//                    m_sprite->m_spriteFlip = SDL_FLIP_HORIZONTAL;
//                    break;
//
//                case SDLK_SPACE: {
//                    int x = m_transform->m_position.Normalize(m_transform->m_position.x);
//                    int y = m_transform->m_position.Normalize(m_transform->m_position.y);
//                    if (m_attributes->m_bombAmount > 0 && Game::Bomb(x, y) == nullptr) {
//
//                        m_attributes->m_bombAmount -= 1;
//                        Game::AddBomb(m_transform->m_position.x, m_transform->m_position.y, m_attributes->m_bombTimer,
//                                      m_attributes->m_explosionDamage, m_attributes->m_explosionRadiusX,
//                                      m_attributes->m_explosionRadiusY,  &m_attributes->m_bombAmount);
//                    }
//                    break;
//                }
//                default:
//                    break;
//            }
//        }

//        if (Game::s_event.type == SDL_KEYUP) {
//
//            switch (Game::s_event.key.keysym.sym) {
//                case SDLK_UP:
//                    m_transform->m_velocity.y = 0;
//                    m_sprite->Play("Idle");
//                    break;
//
//                case SDLK_DOWN:
//                    m_transform->m_velocity.y = 0;
//                    m_sprite->Play("Idle");
//                    break;
//
//                case SDLK_RIGHT:a
//                    break;
//
//                case SDLK_LEFT:
//                    m_transform->m_velocity.x = 0;
//                    m_sprite->Play("Idle");
//                    m_sprite->m_spriteFlip = SDL_FLIP_NONE;
//                    break;
//
//                case SDLK_SPACE:
//                    break;
//
//                default:
//                    //m_sprite->Play("");
//                    break;
//            }
//
//        }
        }
        else if (Game::s_event.type == SDL_KEYUP)
        {
            SDL_KeyCode key = static_cast<SDL_KeyCode>(Game::s_event.key.keysym.sym);

            if (key == m_keys.up) {
                m_transform->m_velocity.y = 0;
                m_sprite->Play("Idle");
            } else if (key == m_keys.down) {
                m_transform->m_velocity.y = 0;
                m_sprite->Play("Idle");
            } else if (key == m_keys.right) {
                m_transform->m_velocity.x = 0;
                m_sprite->Play("Idle");
            } else if (key == m_keys.left) {
                m_transform->m_velocity.x = 0;
                m_sprite->Play("Idle");
                m_sprite->m_spriteFlip = SDL_FLIP_HORIZONTAL;
            }
        }
    }
};

#endif //BOMBERMAN_KEYBOARDCONTROLLER_H