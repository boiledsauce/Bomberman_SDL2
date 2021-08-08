//
// Created by lowIQ on 2021-06-22.
//
#include "Collision.h"
#include "ECS\ColliderComponent.h"

bool Collision::AABB(const SDL_Rect &rectA, const SDL_Rect &rectB, std::string tagOne = "", std::string tagTwo = "")
{
    int marginOfError = 7;

    if (rectA.x + rectA.w >= rectB.x + marginOfError &&
        rectB.x + rectB.w >= rectA.x + marginOfError &&
        rectA.y + rectA.h >= rectB.y + marginOfError &&
        rectB.y + rectB.h >= rectA.y + marginOfError
        )
    {
        return true;
    }

    return false;
}


bool Collision::AABB(const ColliderComponent& colA, const ColliderComponent &colB)
{

    if (colA.m_tag == colB.m_tag)
        return false;


    if (AABB(colA.collider, colB.collider, colA.m_tag, colB.m_tag))
    {

/*
        std::cout << colA.m_tag << " hit: " << colB.m_tag << std::endl;
        std::cout << "WIDTH: " << colA.m_transform->m_width << " W2: " << colB.m_transform->m_width <<  " ";
        std::cout << "WIDTH: " << colA.m_transform->m_height << " W2: " << colB.m_transform->m_height << std::endl;
*/

        return true;
    }

    return false;
}