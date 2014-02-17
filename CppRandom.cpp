#include "CppRandom.hpp"

using namespace std;

CppRandom::CppRandom(unsigned long seed)
{
    _min_std = minstd_rand(seed);
    _min_std0 = minstd_rand0(seed);
    _mt = mt19937(seed);
    _mt_64 = mt19937_64(seed);
    _lux24_b = ranlux24_base(seed);
    _lux48_b = ranlux48_base(seed);
    _lux_24 = ranlux24(seed);
    _lux_48 = ranlux48(seed);
}

CppRandom::~CppRandom()
{
    unif01_DeleteExternGen01(_gen);
}

double CppRandom::get_u01()
{
    return 0.0;
}

unsigned int CppRandom::get_bits(int gen)
{
    switch(gen)
    {
        case 0:
            return _min_std();
        case 1:
            return _min_std0();
        case 2:
            return _mt();
        case 3:
            return _mt_64();
        case 4:
            return _lux24_b();
        case 5:
            return _lux48_b();
        case 6:
            return _lux_24();
        case 7:
            return _lux_48();
        default:
            return 0;
    }
}
