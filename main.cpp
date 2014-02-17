#include "rand.hpp"

using namespace std;

int main(void)
{
    srand(time(NULL)); // Init random seed
    unsigned int seed = rand(); 

    BetterRandom gen = BetterRandom(seed);
    mt19937 mt(seed);

    for(int i=0; i<10; ++i)
    {
        cout << "BetterRandom produced: " << gen.get_rand() << endl;
        cout << "MT produced:           " << mt() << endl;
    }

    gen.test_ext_gen();
    gen.test_gen();

    return 0;
}
