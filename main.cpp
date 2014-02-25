#include "BetterRandom.hpp"
#include "CppRandom.hpp"
#include <iostream>

using namespace std;

int main(void)
{
    srand(time(NULL)); // Seed rand
    unsigned int seed = rand(); 

    // Only one custom generator is allowed at a time
    BetterRandom gen_custom = BetterRandom(seed);
    cout << "================ CUSTOM BIT TEST BELOW ================" << endl << endl;
    gen_custom.test_gen_bits();
    gen_custom.delete_gens();

    CppRandom gen_cpp = CppRandom(seed);
    cout << "================ C++ BIT TEST BELOW ================" << endl;
    gen_cpp.test_gen_bits();

    //for(int i=0; i<10; ++i)
    //{
    //    //cout << "BetterRandom produced: " << gen.get_rand_double() << endl;
    //    //cout << "MT produced:           " << mt() << endl;
    //    cout << "BetterRandom: " << gen.get_rand_int() << endl;
    //    cout << "Seed: " << seed << endl;
    //}

    //cout << endl;

    //for(int i=0; i<8; ++i) // 8 c++ generators
    //{
    //    cout << "C++ gen #" << i << " produced:   " << cpp_gen.get_bits(i) << endl;
    //}

    return 0;
}
