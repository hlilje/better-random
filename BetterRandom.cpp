#include "BetterRandom.hpp"

// Forward declarations
unif01_Gen* BetterRandom::_gen;
unif01_Gen* BetterRandom::_gen_tu01;
unsigned long BetterRandom::_last_num;
uint32_t BetterRandom::_x, BetterRandom::_y, BetterRandom::_z, BetterRandom::_w;

using namespace std;

BetterRandom::BetterRandom(unsigned long seed)
{
    _gen = unif01_CreateExternGen01((char*)"custom", get_rand_double);
    _gen_tu01 = ugfsr_CreateMT19937_98(seed);

    _last_num = seed;

    // Init to Wikipedia values
    _x = 123456789;
    _y = 362436069;
    _z = 521288629;
    _w = 88675123;
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

uint32_t BetterRandom::get_rand_int()
{
    advance_state();
    return _w;
}

unsigned int BetterRandom::get_tu01_rand()
{
    return _gen->GetBits(_gen_tu01->param, _gen_tu01->state);
}

void BetterRandom::advance_state()
{
    uint32_t _t;

    _t = _x ^ (_x << 11);
    _x = _y; _y = _z; _z = _w;
    _w = _w ^ (_w >> 19) ^ (_t ^ (_t >> 8));
}

void BetterRandom::test_gen()
{
    bbattery_SmallCrush(_gen);
}

void BetterRandom::test_tu01_gen()
{
    bbattery_SmallCrush(_gen_tu01);
}
