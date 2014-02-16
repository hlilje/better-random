#include "rand.h"

int main(void)
{
    BetterRandom rand_gen = BetterRandom();

    int next_rand = rand_gen.get_random_number();
    std::cout << next_rand << std::endl;

    return 0;
}
