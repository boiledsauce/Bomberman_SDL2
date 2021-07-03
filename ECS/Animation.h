//
// Created by lowIQ on 2021-06-26.
//

#ifndef BOMBERMAN_ANIMATION_H
#define BOMBERMAN_ANIMATION_H

struct Animation
{
    int index;
    int frames;
    int speed;

    Animation(){}
    Animation(int i, int f, int s)
    {
        index = i;
        frames = f;
        speed = s;
    }
};

#endif //BOMBERMAN_ANIMATION_H
