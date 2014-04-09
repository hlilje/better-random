#include "CppRandom.hpp"

using namespace std;

// Forward declarations
unif01_Gen* CppRandom::_gen_01;
unif01_Gen* CppRandom::_gen_bits;
bool CppRandom::_gens_deleted;

minstd_rand CppRandom::_min_std;
minstd_rand0 CppRandom::_min_std0;
mt19937 CppRandom::_mt;
mt19937_64 CppRandom::_mt_64;
ranlux24_base CppRandom::_lux24_b;
ranlux48_base CppRandom::_lux48_b;
ranlux24 CppRandom::_lux_24;
ranlux48 CppRandom::_lux_48;

CppRandom::CppRandom(unsigned long seed)
{
    // Commented out generators segfaults due to 64 bit
    _min_std = minstd_rand(seed);
    _min_std0 = minstd_rand0(seed);
    _mt = mt19937(seed);
    //_mt_64 = mt19937_64(seed);
    _lux24_b = ranlux24_base(seed);
    //_lux48_b = ranlux48_base(seed);
    _lux_24 = ranlux24(seed);
    //_lux_48 = ranlux48(seed);

    _gen_01 = unif01_CreateExternGen01((char*)"TODO", get_rand_01); // TODO
    //_gen_bits = unif01_CreateExternGenBitsL((char*)"C++11 Mersenne Twister", get_rand_bits_wrapper);

    _gen_bits = unif01_CreateExternGenBitsL((char*)"mt19937", get_rand_bits_wrapper);
}

CppRandom::~CppRandom()
{
    if(!_gens_deleted)
        delete_gens();
}

double CppRandom::get_rand_01()
{
    return 0.4; // TODO
}

unsigned long CppRandom::get_rand_bits(int gen)
{
    switch(gen)
    {
        case 0:
            return _min_std();
        case 1:
            return _min_std0();
        case 2:
            return _mt();
        //case 3:
            //return _mt_64();
        case 4:
            return _lux24_b();
        //case 5:
            //return _lux48_b();
        case 6:
            return _lux_24();
        //case 7:
            //return _lux_48();
        default:
            return 0;
    }
}

unsigned long CppRandom::get_rand_bits_wrapper()
{
    return get_rand_bits(2); // mt
}

void CppRandom::test_gen_01()
{
    bbattery_SmallCrush(_gen_01);
}

void CppRandom::test_gen_bits()
{
    bbattery_SmallCrush(_gen_bits);
}

void CppRandom::test_bits_freq()
{
    // NULL to just print and not save results in datastructure
    // N, n, r, s, L set according to Crush test
    sstring_HammingWeight2(_gen_bits, NULL, 100, pow(10,8), 0, 30, pow(10,6));
    //sstring_HammingWeight2(_gen_bits, NULL, 30, pow(10,8), 20, 10, pow(10,6));

    // N, n, r, s, L set according to BigCrush test
    //sstring_HammingWeight2(_gen_bits, NULL, 10, pow(10,9), 0, 3, pow(10,6));
    //sstring_HammingWeight2(_gen_bits, NULL, 10, pow(10,9), 27, 3, pow(10,6));
}

void CppRandom::delete_gens()
{
    if(!_gens_deleted)
    {
        unif01_DeleteExternGen01(_gen_01);
        unif01_DeleteExternGenBitsL(_gen_bits);
        _gens_deleted = true;
    }
}

void CppRandom::time_gen()
{
    // long n = number of calls to gen
    // lebool fU01 = TRUE for GetU01 test, FALSE for GetBits
    unif01_TimerGenWr(_gen_bits, pow(2, 28), FALSE);
}
