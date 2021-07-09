//
// Created by lowIQ on 2021-06-17.
//

#ifndef BOMBERMAN_ECS_H
#define BOMBERMAN_ECS_H

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;
class Manager;

using ComponentID = std::size_t;
using Group = std::size_t;

inline ComponentID getNewComponentID()
{
    static ComponentID lastID = 0u;
    return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept
{
    static ComponentID typeID = getNewComponentID();
    return typeID;
}

constexpr std::size_t maxComponents = 32;
constexpr std::size_t maxGroups = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using GroupBitset = std::bitset<maxGroups>;

using ComponentArray = std::array<Component*, maxComponents>;

class Component {
public:
    Entity* m_entity;
    virtual void init() {}
    virtual void update() {}
    virtual void draw() {}
    virtual ~Component() {}
};

class Entity
{
private:
    static int s_entityCount;
    int m_entityID;
    Manager& m_manager;
    bool m_active = true;
    std::vector<std::unique_ptr<Component>> m_components;
    ComponentArray m_componentArray;
    ComponentBitSet m_componentBitSet;
    GroupBitset m_groupBitset;

public:
    Entity(Manager& manager) : m_manager(manager){m_entityID = s_entityCount++;}
    int entityID(){return m_entityID;}

    void update()
    {
        for (auto& c : m_components)
        {
                c->update();
        }
    }
    void draw()
    {
        for (auto& c : m_components){ c->draw(); }
    }
    bool isActive() { return m_active; }
    void destroy() { m_active = false; }
    bool hasGroup(Group mGroup)
    {
        return m_groupBitset[mGroup];
    }

    void addGroup(Group mGroup);
    void removeGroup(Group mGroup);



    void deleteGroup(Group mGroup)
    {
        m_groupBitset[mGroup] = false;
    }

    template <typename T> bool hasComponent() const
    {
        return m_componentBitSet[getComponentTypeID<T>()];
    }

    template <typename T, typename... TArgs>
    T& addComponent(TArgs&& ... mArgs)
    {
        T* c(new T(std::forward<TArgs>(mArgs) ... ));
        c->m_entity = this;
        std::unique_ptr<Component> uPtr{ c };
        m_components.emplace_back(std::move(uPtr));

        m_componentArray[getComponentTypeID<T>()] = c;
        m_componentBitSet[getComponentTypeID<T>()] = true;

        c->init();
        return *c;
    }


    template<typename T> T& getComponent() const
    {
        auto ptr(m_componentArray[getComponentTypeID<T>()]);
        return *static_cast<T*>(ptr);
    }

    template<typename T> void removeComponent()
    {
        m_componentBitSet[getComponentTypeID<T>()] = false;
        m_componentArray[getComponentTypeID<T>()] = nullptr;
    }

};

class Manager
{
private:
    std::vector<std::unique_ptr<Entity>> m_entities;
    std::array<std::vector<Entity*>, maxGroups> groupedEntities;
public:
    void update()
    {
        for (auto& e : m_entities)
        {
            e->update();
        }
    }
    void draw()
    {
        for (auto& e : m_entities)
            e->draw();
    }

    void refresh()
    {
        for(auto i(0u); i < maxGroups; i++)
        {
            auto &curVector(groupedEntities[i]);
            curVector.erase(std::remove_if(std::begin(curVector), std::end(curVector), [i](Entity* mEntity)
            {
                return !mEntity->isActive() || !mEntity->hasGroup(i);
            }
            ), std::end(curVector));
        }

       m_entities.erase(std::remove_if(std::begin(m_entities), std::end(m_entities), [] (const std::unique_ptr<Entity> &mEntity)
       {
        return ! mEntity->isActive();
        }), std::end(m_entities));
    }

    void AddToGroup(Entity* mEntity, Group mGroup)
    {
        groupedEntities[mGroup].emplace_back(mEntity);
    }

    std::vector<Entity*>& getGroup(Group mGroup)
    {
        return groupedEntities[mGroup];
    }

    Entity& addEntity()
    {
        Entity* e = new Entity(*this);
        std::unique_ptr<Entity> uPtr{e};
        m_entities.emplace_back(std::move(uPtr));
        return *e;
    }

};
#endif //BOMBERMAN_ECS_H
