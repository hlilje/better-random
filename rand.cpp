#include "rand.hpp"

using namespace std;

BetterRandom::BetterRandom()
{
    //unif01_Gen* gen; // Generic generator to implement

    unsigned long seed = 1;
    unif01_Gen* MT = ugfsr_CreateMT19937_98(seed);
    ugfsr_DeleteGen(MT);
}

BetterRandom::~BetterRandom()
{
}

int BetterRandom::get_random_number()
{
    return 4;
}
