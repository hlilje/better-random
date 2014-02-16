//#pragma once

#include <iostream>
//#include <random>
extern "C"
{
//#include <cstdlib> // rand
#include "unif01.h" // Generic
#include "ugfsr.h" // GFSR etc.
}

class BetterRandom
{
public:
    BetterRandom();
    ~BetterRandom();

    int get_random_number();

    // TestU01
    //unif01_Gen* ugfsr_CreateMT19937_98(unsigned long seed);
    //void ugfsr_DeleteGen(unif01_Gen* gen);
};
