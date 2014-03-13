#include "BetterRandom.hpp"

using namespace std;

// Forward declarations
unif01_Gen* BetterRandom::_gen_01;
unif01_Gen* BetterRandom::_gen_bits;
unif01_Gen* BetterRandom::_gen_tu01;
bool BetterRandom::_gens_deleted;

unsigned long BetterRandom::_last_num;
uint32_t BetterRandom::_x, BetterRandom::_y, BetterRandom::_z, BetterRandom::_w;
//uint32_t BetterRandom::_x, BetterRandom::_y, BetterRandom::_z, BetterRandom::_w, BetterRandom::_s;

uint32_t BetterRandom::_Q[QSIZE];
uint32_t BetterRandom::_c;
#define PHI 0x9e3779b9

unsigned long BetterRandom::_buffer[BUFFERSIZE];

hash<string> BetterRandom::_hasher;

BetterRandom::BetterRandom(unsigned long seed)
{
    _gen_01 = unif01_CreateExternGen01((char*)"custom", get_rand_01);
    _gen_bits = unif01_CreateExternGenBitsL((char*) "Custom XORShift + Seed", get_rand_bits);
    _gen_tu01 = ugfsr_CreateMT19937_98(seed);
    _gens_deleted = false;

    _last_num = seed;

    // Init XORShift to Wikipedia values
    _x = 123456789;
    _y = 362436069;
    _z = 521288629;
    //_w = 88675123;
    //_s = 88675123; // Addition to original algorithm
    _w = seed; // Use seed to avoid identical series

    // Init multiply with carry according to Wikipedia
    //_c = 362436;
    //uint32_t x = (uint32_t)seed;
    //int i;

    //_Q[0] = x;
    //_Q[1] = x + PHI;
    //_Q[2] = x + PHI + PHI;

    //for (i = 3; i < QSIZE; i++)
    //    _Q[i] = _Q[i - 3] ^ _Q[i - 2] ^ PHI ^ i;

    //_hasher = hash<string>();
}

BetterRandom::~BetterRandom()
{
    if(!_gens_deleted)
        delete_gens();
}

double BetterRandom::get_rand_01()
{
    advance_state();
    return (double)_last_num; // TODO Get real double
}

unsigned long BetterRandom::get_rand_bits()
{
    advance_state();
    return (unsigned long)_w;
    //return (unsigned long)Q[(4095 + 1) & 4095];
    //return _last_num;

}

unsigned long BetterRandom::get_rand_tu01()
{
    return _gen_tu01->GetBits(_gen_tu01->param, _gen_tu01->state);
}

void BetterRandom::advance_state()
{
    //_s = _w; // Save last value
    // XORSHIFT
    uint32_t t, u, v;
    //uint32_t t;
    //for(int i=0; i<BUFFERSIZE; ++i)
    //{
        //_t = _x ^ (_x << 11);
        //_x = _y; _y = _z; _z = _w;
        //_w = _w ^ (_w >> 19) ^ (_t ^ (_t >> 8));
        //_buffer[i] = _w;

        t = _x ^ (_x << 11);
        _x = _y; _y = _z; _z = _w;
        _w = _w ^ (_w >> 19) ^ (t ^ (t >> 8));

        // Passes all tests
        //u = _w & 0x0000FFFF;
        //u = u << 16;
        //v = _w & 0xFFFF0000;
        //v = v >> 16;
        //v = v & 0x0000FFFF;
        //_w = u | v;

        //u = _w & 0x000000FF;
        //u = u << 24;
        //v = _w & 0xFF000000;
        //v = v >> 24;
        //v = v & 0x000000FF;
        //_w = u | v;

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
        //v = v & 0x0FFFFFFF;
        //_w = u | v;

        //_w = _w ^ _s;

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
    //}
    
    //_w = _buffer[rand() % BUFFERSIZE];

    //string s = to_string(_w);
    //_w = _hasher(s);

    // LCG
    //unsigned long a = 48271;
    //unsigned long c = 0;
    //unsigned long m = pow(2,31) - 1;
    //_last_num = (_last_num * a + c) % m;  

    // MULTIPLY WITH CARRY
    //uint32_t i = 4095;
    //uint64_t t;

    //i = (i + 1) & 4095;
    //t = (18705ULL * Q[i]) + c;
    //c = t >> 32;
    //Q[i] = 0xfffffffe - t;

    // C++11 HASH
    // TODO Segfaults at sknuth_MaxOft test
    //string s = to_string(_last_num);
    //for(int i=0; i<10; ++i)
    //{
    //    _last_num = _hasher(s);
    //}
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
