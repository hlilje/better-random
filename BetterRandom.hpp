//#pragma once

#include <random>
#include <functional> // Hash
#include <cstdlib>
#include <ctime>
#include <cstdint>
extern "C"
{
#include "unif01.h" // Generic
#include "ugfsr.h" // GFSR etc.
#include "bbattery.h" // Battery of tests
#include "sstring.h" // Test strings of random bits
}

#define QSIZE 4096
#define BUFFERSIZE 3 

class BetterRandom
{
public:
    BetterRandom(unsigned long);
    ~BetterRandom();

    static double get_rand_01(void); // Must return double in [0, 1)
    static unsigned long get_rand_bits(void); // Must return unsigned int in [0, 2^32 - 1]
    static unsigned long get_rand_tu01(void); // Get random number from TestU01 generator

    static void test_gen_01(void); // Perform TestU01 test battery on custom gen (double)
    static void test_gen_bits(void); // Perform TestU01 test battery on custom gen (uint)
    static void test_gen_tu01(void); // Perform TestU01 test battery on TestU01 gen
    static void test_bits_freq(void); // Perform a Frequency Test (uint)

    static void delete_gens(void); // Manually delete gens before destructor

private:
    static unif01_Gen* _gen_01; // Custom gen (double)
    static unif01_Gen* _gen_bits; // Custom gen (uint)
    static unif01_Gen* _gen_tu01; // TestU01 gen
    static bool _gens_deleted; // To avoid segfaulting by deleting twice

    static unsigned long _last_num; // TODO Last generated value

    static uint32_t _x, _y, _z, _w; // For Xorshift
    static uint32_t _Q[QSIZE], _c; // For multiply with carry

    static std::hash<std::string> _hasher; // Holds the hash function

    static unsigned long _buffer[BUFFERSIZE]; // To build up a buffer of random numbers

    // Move internal state forward one step
    static void advance_state(void);
};
