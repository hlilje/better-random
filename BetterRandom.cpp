#include "BetterRandom.hpp"

using namespace std;

// Forward declarations
unif01_Gen* BetterRandom::_gen_01;
unif01_Gen* BetterRandom::_gen_bits;
unif01_Gen* BetterRandom::_gen_tu01;
bool BetterRandom::_gens_deleted;

//unsigned long BetterRandom::_last_num;
uint32_t BetterRandom::_x, BetterRandom::_y, BetterRandom::_z, BetterRandom::_w;

BetterRandom::BetterRandom(unsigned long seed)
{
    _gen_01 = unif01_CreateExternGen01((char*)"TODO", get_rand_01); // TODO
    _gen_bits = unif01_CreateExternGenBitsL((char*) "Custom XORShift + Seed", get_rand_bits);
    _gen_tu01 = ugfsr_CreateMT19937_98(seed); // Internal Mersenne Twister from TestU01
    _gens_deleted = false;

    //_last_num = seed;

    // Init XORShift to Wikipedia values
    _x = 123456789;
    _y = 362436069;
    _z = 521288629;
    //_w = 88675123;
    _w = seed; // Use seed to avoid identical series
}

BetterRandom::~BetterRandom()
{
    if(!_gens_deleted)
        delete_gens();
}

double BetterRandom::get_rand_01()
{
    advance_state();
    return 0.4; // TODO
}

unsigned long BetterRandom::get_rand_bits()
{
    advance_state();
    return (unsigned long)_w;
    //return _last_num;

}

unsigned long BetterRandom::get_rand_tu01()
{
    return _gen_tu01->GetBits(_gen_tu01->param, _gen_tu01->state);
}

void BetterRandom::advance_state()
{
    // Custom XORShift
    uint32_t t, u, v;
    t = _x ^ (_x << 11);
    _x = _y; _y = _z; _z = _w;
    _w = _w ^ (_w >> 19) ^ (t ^ (t >> 8));

    // Doesn't pass all tests
    //u = _w & 0x000000FF;
    //u = u << 24;
    //v = _w & 0xFF000000;
    //v = v >> 24;
    //v = v & 0x000000FF;
    //_w = u | v;

    // Doesn't pass all tests
    //u = _w & 0x00000FFF;
    //u = u << 20;
    //v = _w & 0xFFF00000;
    //v = v >> 20;
    //v = v & 0x00000FFF;
    //_w = u | v;

    // Passes all tests
    //u = _w & 0x0F0F0F0F;
    //u = u << 4;
    //v = _w & 0xF0F0F0F0;
    //v = v >> 4;
    //_w = u | v;

    // Passes all tests
    u = _w & 0x0000FFFF;
    u = u << 16;
    v = _w & 0xFFFF0000;
    v = v >> 16;
    _w = u | v;
}

void BetterRandom::test_gen_01()
{
    bbattery_SmallCrush(_gen_01);
}

void BetterRandom::test_gen_bits()
{
    bbattery_SmallCrush(_gen_bits);
}

void BetterRandom::test_gen_tu01()
{
    bbattery_SmallCrush(_gen_tu01);
}

void BetterRandom::test_bits_freq()
{
    // NULL to just print and not save results in datastructure
    // N, n, r, s, L set according to Crush test
    //sstring_HammingWeight2(_gen_bits, NULL, 100, pow(10,8), 0, 30, pow(10,6));
    sstring_HammingWeight2(_gen_bits, NULL, 100, pow(10,6), 0, 30, pow(10,6));
    //sstring_HammingWeight2(_gen_bits, NULL, 30, pow(10,8), 20, 10, pow(10,6));

    // N, n, r, s, L set according to BigCrush test
    //sstring_HammingWeight2(_gen_bits, NULL, 10, pow(10,9), 0, 3, pow(10,6));
    //sstring_HammingWeight2(_gen_bits, NULL, 10, pow(10,9), 27, 3, pow(10,6));
}

void BetterRandom::delete_gens()
{
    if(!_gens_deleted)
    {
        unif01_DeleteExternGen01(_gen_01);
        unif01_DeleteExternGenBitsL(_gen_bits);
        ugfsr_DeleteGen(_gen_tu01);
        _gens_deleted = true;
    }
}
