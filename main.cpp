#include "BetterRandom.hpp"
#include "CppRandom.hpp"

using namespace std;

int main(void)
{
    srand(time(NULL)); // Seed rand
    unsigned int seed = rand(); 

    BetterRandom gen = BetterRandom(seed);
    //CppRandom cpp_gen = CppRandom(seed);
    //mt19937 mt(seed);

    for(int i=0; i<10; ++i)
    {
        //cout << "BetterRandom produced: " << gen.get_rand_double() << endl;
        //cout << "MT produced:           " << mt() << endl;
        cout << gen.get_rand_int() << endl;
    }

    //cout << endl;

    //for(int i=0; i<8; ++i) // 8 c++ generators
    //{
    //    cout << "C++ gen #" << i << " produced:   " << cpp_gen.get_bits(i) << endl;
    //}

    //gen.test_gen();
    //gen.test_tu01_gen();

    return 0;
}
