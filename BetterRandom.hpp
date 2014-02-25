//#pragma once

#include <random>
#include <cstdlib>
#include <ctime>
#include <cstdint>
extern "C"
{
#include "unif01.h" // Generic
#include "ugfsr.h" // GFSR etc.
#include "bbattery.h"
}

class BetterRandom
{
public:
    BetterRandom(unsigned int);
    ~BetterRandom();

    static double get_rand_01(void); // Must return double in [0, 1)
    static unsigned int get_rand_bits(void); // Must return unsigned int in [0, 2^32 - 1]
    static unsigned int get_rand_tu01(void); // Get random number from TestU01 generator

    static void test_gen_01(void); // Perform a TestU01 test on custom gen (double)
    static void test_gen_bits(void); // Perform a TestU01 test on custom gen (uint)
    static void test_gen_tu01(void); // Perform a TestU01 test on TestU01 gen

    static void delete_gens(void); // Manually delete gens before destructor

private:
    static unif01_Gen* _gen_01; // Custom gen (double)
    static unif01_Gen* _gen_bits; // Custom gen (uint)
    static unif01_Gen* _gen_tu01; // TestU01 gen
    static bool _gens_deleted; // To avoid segfaulting by deleting twice

    static unsigned int _last_num; // TODO Last generated value

    static uint32_t _x, _y, _z, _w; // For Xorshift

    // Move internal state forward one step
    static void advance_state(void);
};
