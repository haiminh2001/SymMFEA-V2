#include "evolution/reproducer/crossover.h"

Crossover::Crossover(int max_length, int max_depth)
{
    this->max_depth = max_depth;
    this->max_length = max_length;
}

std::vector<Individual*> Crossover::call(SubPopulation &subpop)
{
    std::vector<Individual*> children;

    while (children.size() < subpop.num_individual)
    {

        auto i1 = subpop.get_random();
        auto i2 = subpop.get_random();

        auto c = this->call(i1, i2);

        children.insert(children.end(), c.begin(), c.end());
    }

    return children;
}

std::vector<std::vector<Individual*>> Crossover::call(Population &population)
{
    std::vector<std::vector<Individual*>> children;
    for (auto subpop : population.sub_populations)
    {
        children.push_back(this->call(subpop));
    }
    return children;
}