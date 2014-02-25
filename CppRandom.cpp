#include "CppRandom.hpp"

using namespace std;

// Forward declarations
unif01_Gen* CppRandom::_gen_01;
unif01_Gen* CppRandom::_gen_bits;
minstd_rand CppRandom::_min_std;
minstd_rand0 CppRandom::_min_std0;
mt19937 CppRandom::_mt;
mt19937_64 CppRandom::_mt_64;
ranlux24_base CppRandom::_lux24_b;
ranlux48_base CppRandom::_lux48_b;
ranlux24 CppRandom::_lux_24;
ranlux48 CppRandom::_lux_48;
bool CppRandom::_gens_deleted;

CppRandom::CppRandom(unsigned int seed)
{
    _min_std = minstd_rand(seed);
    _min_std0 = minstd_rand0(seed);
    _mt = mt19937(seed);
    _mt_64 = mt19937_64(seed);
    _lux24_b = ranlux24_base(seed);
    _lux48_b = ranlux48_base(seed);
    _lux_24 = ranlux24(seed);
    _lux_48 = ranlux48(seed);

    _gen_01 = unif01_CreateExternGen01((char*)"TODO", get_rand_01); // TODO
    _gen_bits = unif01_CreateExternGenBits((char*)"C++11 Mersenne Twister", get_rand_bits_wrapper);
}

CppRandom::~CppRandom()
{
    if(!_gens_deleted)
        delete_gens();
}

double CppRandom::get_rand_01()
{
    return 0.1; // TODO
}

unsigned int CppRandom::get_rand_bits(int gen)
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

unsigned int CppRandom::get_rand_bits_wrapper()
{
    return get_rand_bits(2);
}

void CppRandom::test_gen_01()
{
    bbattery_SmallCrush(_gen_01);
}

void CppRandom::test_gen_bits()
{
    bbattery_SmallCrush(_gen_bits);
}

void CppRandom::delete_gens()
{
    if(!_gens_deleted)
    {
        unif01_DeleteExternGen01(_gen_01);
        unif01_DeleteExternGenBits(_gen_bits);
        _gens_deleted = true;
    }
}
