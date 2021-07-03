//
// Created by lowIQ on 2021-06-22.
//

#ifndef BOMBERMAN_COLLISION_H
#define BOMBERMAN_COLLISION_H
#include <SDL.h>
#include <string>

class ColliderComponent;

class Collision
{
public:
    static bool AABB(const SDL_Rect& rectA, const SDL_Rect& rectB, std::string tagOne, std::string tagTwo); // Axis aligned bounding box
    static bool AABB(const ColliderComponent& colA, const ColliderComponent &colB);
};


#endif //BOMBERMAN_COLLISION_H
