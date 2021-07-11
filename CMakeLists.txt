cmake_minimum_required(VERSION 3.19)
project(bomberman)

set(CMAKE_CXX_STANDARD 14)

set(SDL2_INCLUDE_DIR C:/Users/lowIQ/OneDrive/Skrivbord/SDL/SDL2-2.0.14/include)
set(SDL2_LIB_DIR C:/Users/lowIQ/OneDrive/Skrivbord/SDL/SDL2-2.0.14/lib/x86)
include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})

add_executable(bomberman main.cpp Game.cpp Game.h TextureManager.h TextureManager.cpp GameObject.cpp GameObject.h Map.cpp Map.h ECS/ECS.h ECS/Components.h ECS/SpriteComponent.h ECS/TransformComponent.h Vector2D.h Vector2D.cpp ECS/KeyboardController.h ECS/ColliderComponent.h Collision.h Collision.cpp ECS/TileComponent.h Constants.h ECS/ECS.cpp ECS/Animation.h AssetManager.h AssetManager.cpp ECS/BombComponent.h ECS/CreatureAttributeComponent.h ECS/BlockComponent.h ECS/ExplosionComponent.h ECS/RewardComponent.h RandomNumber.h RandomNumber.cpp)
target_link_libraries(${PROJECT_NAME} SDL2main SDL2 SDL2_image SDL2_ttf)




