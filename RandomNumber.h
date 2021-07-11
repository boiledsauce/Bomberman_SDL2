//
// Created by lowIQ on 2021-07-11.
//

#ifndef BOMBERMAN_RANDOMNUMBER_H
#define BOMBERMAN_RANDOMNUMBER_H
#include <random>
using MyRNG = std::mt19937;

class RandomNumber
{
public:
    static MyRNG randEngine;
//    static int seed_val;

//    RandomNumber()
//    {
//            randEngine.seed(seed_val);
//    }

    static int interval(int a, int b)
    {
        std::uniform_int_distribution<int> range(a,b);
        return range(randEngine);
    }
};

#endif //BOMBERMAN_RANDOMNUMBER_H
