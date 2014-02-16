//#pragma once

#include <iostream>
#include <random>
#include <cstdlib> // rand
extern "C"
{
#include "unif01.h" // Generic
#include "ugfsr.h" // GFSR etc.
}

class BetterRandom
{
public:
    BetterRandom(unsigned long);
    ~BetterRandom();

    double get_rand();
    int get_random_number();

private:
    unif01_Gen* _gen;
};
