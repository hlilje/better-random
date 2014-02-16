#include "rand.hpp"

using namespace std;

BetterRandom::BetterRandom(unsigned long seed)
{
    _gen = ugfsr_CreateMT19937_98(seed);
}

BetterRandom::~BetterRandom()
{
    ugfsr_DeleteGen(_gen);
}

double BetterRandom::get_rand()
{
    return _gen->GetU01(_gen->param, _gen->state);
}

int BetterRandom::get_random_number()
{
    return 4;
}
