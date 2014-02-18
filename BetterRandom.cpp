#include "BetterRandom.hpp"

// Forward declarations
unif01_Gen* BetterRandom::_gen;
unif01_Gen* BetterRandom::_gen_tu01;
unsigned long BetterRandom::_last_num;

using namespace std;

BetterRandom::BetterRandom(unsigned long seed)
{
    _gen = unif01_CreateExternGen01((char*)"custom", get_rand_double);
    _gen_tu01 = ugfsr_CreateMT19937_98(seed);

    _last_num = seed;
}

BetterRandom::~BetterRandom()
{
    unif01_DeleteExternGen01(_gen);
    ugfsr_DeleteGen(_gen_tu01);
}

double BetterRandom::get_rand_double()
{
    advance_state();
    return (double)_last_num;
}

unsigned long BetterRandom::get_rand_long()
{
    advance_state();
    return _last_num;
}

unsigned int BetterRandom::get_tu01_rand()
{
    return _gen->GetBits(_gen_tu01->param, _gen_tu01->state);
}

void BetterRandom::advance_state()
{
    unsigned long x = _last_num << 2;
    x = x ^ 18378283;
    x = x >> 4;
    _last_num = x;
}

void BetterRandom::test_gen()
{
    bbattery_SmallCrush(_gen);
}

void BetterRandom::test_tu01_gen()
{
    bbattery_SmallCrush(_gen_tu01);
}
