//#pragma once

#include <random>
extern "C"
{
#include "unif01.h" // Generic
#include "bbattery.h" // Battery of tests
#include "sstring.h" // Test strings of random bits
}

class CppRandom
{
public:
    CppRandom(unsigned int);
    ~CppRandom();

    static double get_rand_01(void);
    static unsigned int get_rand_bits(int); // Get random uint from given gen index
    static unsigned int get_rand_bits_wrapper(); // Wrapper to pass to TU01 test

    static void test_gen_01(void); // Perform TestU01 battery test on c++ gen (double)
    static void test_gen_bits(void); // Perform TestU01 battery test on c++ gen (uint)
    static void test_bits_freq(void); // Perform a Frequency Test (uint)

    static void delete_gens(void); // Manually delete gens before destructor

private:
    static unif01_Gen* _gen_01;
    static unif01_Gen* _gen_bits;
    static bool _gens_deleted; // To avoid segfaulting by deleting twice

    static std::minstd_rand _min_std;
    static std::minstd_rand0 _min_std0;
    static std::mt19937 _mt;
    static std::mt19937_64 _mt_64;
    static std::ranlux24_base _lux24_b;
    static std::ranlux48_base _lux48_b;
    static std::ranlux24 _lux_24;
    static std::ranlux48 _lux_48;
};
