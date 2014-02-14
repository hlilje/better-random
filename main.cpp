#include "rand.h"

int main(void)
{
    BetterRandom* rand_gen = new BetterRandom();

    int next_rand = rand_gen->get_random_number();
    std::cout << next_rand << std::endl;

    delete rand_gen;

    return 0;
}
