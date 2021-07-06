//
// Created by lowIQ on 2021-06-18.
//

#ifndef BOMBERMAN_SPRITECOMPONENT_H
#define BOMBERMAN_SPRITECOMPONENT_H

#include "Components.h"
#include "SDL.h"
#include "../TextureManager.h"
#include "Animation.h"
#include <map>

class SpriteComponent : public Component
{
private:
    TransformComponent *m_transform;
    SDL_Texture* m_texture;
    SDL_Rect srcRect, destRect;

    bool m_animated = false;
    int m_frames = 0;
    int m_speed = 100; // delay between frames


public:
    int m_animationIx = 0;
    std::map<const char*, Animation> m_animations;

    SDL_RendererFlip m_spriteFlip = SDL_FLIP_NONE;
    SDL_Texture* getTexture(){ return m_texture; }
    SDL_Rect &getsrcRect(){ return srcRect; }
    SDL_Rect &getdestRect(){ return destRect; }

    SpriteComponent() = default;
    SpriteComponent(const char* path)
    {
        setTexture(path);
    }

    SpriteComponent(const char* path, bool isAnimated)
    {
        m_animated = isAnimated;
        Animation idle = Animation(0, 1, 100);
        Animation walk = Animation(0, 4, 3);
        m_animations.emplace("Idle", idle);
        m_animations.emplace("Walk", walk);
        Play("Idle");
        setTexture(path);
    }

    ~SpriteComponent()
    {
        SDL_DestroyTexture(m_texture);
    }

    void setTexture(const char* path)
    {
        m_texture = TextureManager::LoadTexture(path);
    }

    void init() override
    {
        m_transform = &m_entity->getComponent<TransformComponent>();

        srcRect.x = srcRect.y = 0;
        srcRect.w = m_transform->m_width;
        srcRect.h = m_transform->m_height;

        destRect.w = m_transform->m_width * m_transform->m_scale;
        destRect.h = m_transform->m_height * m_transform->m_scale;
    }

    void update() override
    {
        if (m_animated)
        {
           srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / m_speed) % m_frames); // 1000 / 20 % 4 => 50 % 4 == 2
        }

        srcRect.y = m_animationIx * m_transform->m_height;

        destRect.w = m_transform->m_width * m_transform->m_scale;
        destRect.w = m_transform->m_height * m_transform->m_scale;

        destRect.x = static_cast<int>(m_transform->m_position.x);
        destRect.y = static_cast<int>(m_transform->m_position.y);
    }

    void draw() override
    {
        TextureManager::Draw(m_texture, srcRect, destRect, m_spriteFlip);
    }

    void Play(const char* animName)
    {
        m_frames = m_animations[animName].frames;
        m_animationIx = m_animations[animName].index;
        m_speed = m_animations[animName].speed;
    }

};

#endif //BOMBERMAN_SPRITECOMPONENT_H
