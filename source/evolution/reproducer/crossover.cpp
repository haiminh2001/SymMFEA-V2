#include "evolution/reproducer/crossover.h"
#include "iostream"

std::vector<Individual *> Crossover::call(SubPopulation *subpop)
{
    std::vector<Individual *> children;

    uint64_t max_num_crossover_failures = ((uint64_t) subpop->num_individual) * ((uint64_t) subpop->num_individual);

    while (children.size() < subpop->num_individual)
    {

        auto i1 = subpop->get_random();
        auto i2 = subpop->get_random();

        auto c = this->call(i1, i2);

        if (c.size() == 0)
            max_num_crossover_failures -= 1;
        else
        {
            max_num_crossover_failures += c.size();
            children.insert(children.end(), c.begin(), c.end());
        }

        if (max_num_crossover_failures == 0)
        {
            std::cout << "\nWarning! Crossover cannot create new valid offsprings!!\n";
            break;
        }
    }

    return children;
}

std::vector<std::vector<Individual *>> Crossover::call(Population* population)
{
    std::vector<std::vector<Individual *>> children;
    for (auto subpop : population->sub_populations)
    {
        children.push_back(this->call(subpop));
    }
    return children;
}