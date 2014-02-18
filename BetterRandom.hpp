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

    static double get_rand_double(void); // Must return double in [0, 1)
    static unsigned long get_rand_long(void); // Should be [0, 2^32 - 1]
    static unsigned int get_tu01_rand(void); // Get random number from TestU01 generator

    static void test_gen(void); // Perform a TestU01 test on custom gen
    static void test_tu01_gen(void); // Perform a TestU01 test on TestU01 gen

private:
    static unif01_Gen* _gen; // Custom gen
    static unif01_Gen* _gen_tu01; // TestU01 gen

    static unsigned long _last_num; // Last generated value

    // Move internal state forward one step
    static void advance_state(void);
};
