//#pragma once

#include <iostream>
#include <random>
#include <cstdlib>
#include <ctime>
extern "C"
{
#include "unif01.h" // Generic
#include "ugfsr.h" // GFSR etc.
#include "bbattery.h"
}

class BetterRandom
{
public:
    BetterRandom(unsigned long);
    ~BetterRandom();

    unsigned int get_rand(); // Get random number from TestU01 generator
    int get_random_number(); // Relevant

    void test_gen(); // Perform a TestU01 test on TestU01 gen
    void test_ext_gen(); // Perform a TestU01 test on custom gen

private:
    unif01_Gen* _gen; // TestU01 gen
    unif01_Gen* _ext_gen; // Custom gen

    // Static to be able to pass as func pointer in C
    static double get_ext_rand(void); // Must return double in [0, 1)
};
