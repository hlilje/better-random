#include "BetterRandom.hpp"
#include "CppRandom.hpp"
#include <iostream>

using namespace std;

int main(void)
{
    srand(time(NULL)); // Seed rand
    unsigned long seed = rand(); 

    // Only one custom generator is allowed at a time
    BetterRandom gen_custom = BetterRandom(seed);
    cout << "================== CUSTOM BIT TEST BELOW ==================" << endl;
    gen_custom.test_gen_bits();
    //gen_custom.test_bits_freq();

    for(int i=0; i<2000; ++i)
    {
        cout << gen_custom.get_rand_bits() << " ";
    }
    cout << endl;
    gen_custom.delete_gens();

    //CppRandom gen_cpp = CppRandom(seed);
    //cout << "=================== C++ BIT TEST BELOW ====================" << endl;
    //gen_cpp.test_gen_bits();
    //gen_cpp.test_bits_freq();
    //gen_cpp.delete_gens();

    //for(int i=0; i<8; ++i) // 8 C++ generators
    //{
    //    cout << "C++ gen #" << i << " produced:   " << cpp_gen.get_bits(i) << endl;
    //}

    return 0;
}
