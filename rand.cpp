#include "rand.hpp"

using namespace std;

BetterRandom::BetterRandom(unsigned long seed)
{
    _gen = ugfsr_CreateMT19937_98(seed);

    _ext_gen = unif01_CreateExternGen01((char*)"custom", get_ext_rand);
}

BetterRandom::~BetterRandom()
{
    ugfsr_DeleteGen(_gen);
    unif01_DeleteExternGen01(_ext_gen);
}

unsigned int BetterRandom::get_rand()
{
    return _gen->GetBits(_gen->param, _gen->state); // [0, 2^32 - 1]
}

int BetterRandom::get_random_number()
{
    return 4;
}

void BetterRandom::test_ext_gen()
{
    bbattery_SmallCrush(_ext_gen);
}

void BetterRandom::test_gen()
{
    bbattery_SmallCrush(_gen);
}

double BetterRandom::get_ext_rand()
{
    double x = 0.4;
    return x;
}
