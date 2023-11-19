#include <evolution/population/sub_population.h>
#include <components/tree/tree_handler.h>
#include "utils/random_utils.h"
#include <vector>

SubPopulation::SubPopulation(int num_individual, int skill_factor, DataView dataview)
{
    this->skill_factor = skill_factor;
    this->dataview = dataview;

    std::vector<Individual> individuals;
    for (int i = 0; i < num_individual; i++)
    {
        auto tree = create_tree(1, 5, 5);
        individuals.emplace_back(Individual(tree, skill_factor));
    }
    this->individuals = individuals;
    this->num_individual = num_individual;
}

Individual SubPopulation::get_random()
{
    auto idx = Random::randint<int>(0, this->individuals.size() - 1);
    return this->individuals[idx];
}

void SubPopulation::append(std::vector<Individual> offsprings)
{
    this->individuals.insert(this->individuals.end(), offsprings.begin(), offsprings.end());
};