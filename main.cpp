#include "BetterRandom.hpp"
#include "CppRandom.hpp"

using namespace std;

int main(void)
{
    srand(time(NULL)); // Seed rand
    unsigned int seed = rand(); 

    BetterRandom gen = BetterRandom(seed);
    CppRandom cpp_gen = CppRandom(seed);
    mt19937 mt(seed);

    for(int i=0; i<10; ++i)
    {
        cout << "BetterRandom produced: " << gen.get_rand() << endl;
        cout << "MT produced:           " << mt() << endl;
    }

    cout << endl;

    for(int i=0; i<8; ++i) // 8 c++ generators
    {
        cout << "C++ gen #" << i << " produced:   " << cpp_gen.get_bits(i) << endl;
    }

    //gen.test_ext_gen();
    //gen.test_gen();

    return 0;
}
