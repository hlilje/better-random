#include "rand.hpp"

using namespace std;

int main(void)
{
    unsigned int seed = rand();
    BetterRandom gen = BetterRandom(seed);

    mt19937 mt(seed);

    for(int i=0; i<10; ++i)
    {
        cout << "BetterRandom produced: " << gen.get_rand() << endl;
        cout << "MT produced:           " << mt() << endl;
    }

    return 0;
}
