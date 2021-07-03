#include "Game.h"
#include "Constants.h"
Game *game = nullptr;

int main( int argc, char* args[] )
{
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    game = new Game();
    game->init("Bomberman game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, /*1920*/800, 800
               /*1080*/, false);
    while(game->running())
    {
        frameStart = SDL_GetTicks();

        game->handleEvents();   //handle any user input
        game->update();         //update all object eg. positions etc.
        game->render();         //render changes to the display

        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    return 0;
}