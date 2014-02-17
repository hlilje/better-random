//#pragma once

#include <random>
extern "C"
{
#include "unif01.h" // Generic
}

class CppRandom
{
public:
    CppRandom(unsigned long);
    ~CppRandom();

    double get_u01(void);
    unsigned int get_bits(int); // Get a random int from given gen index

private:
    unif01_Gen* _gen;

    std::minstd_rand _min_std;
    std::minstd_rand0 _min_std0;
    std::mt19937 _mt;
    std::mt19937_64 _mt_64;
    std::ranlux24_base _lux24_b;
    std::ranlux48_base _lux48_b;
    std::ranlux24 _lux_24;
    std::ranlux48 _lux_48;
};
