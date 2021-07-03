//
// Created by lowIQ on 2021-06-24.
//
#include "ECS.h"

void Entity::addGroup(Group mGroup)
{
    m_groupBitset[mGroup] = true;
    m_manager.AddToGroup(this, mGroup);
}

void Entity::removeGroup(Group mGroup)
{
    m_groupBitset[mGroup] = false;
    m_manager.AddToGroup(this, false);
}
