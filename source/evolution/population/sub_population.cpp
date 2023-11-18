#include <evolution/population/sub_population.h>
#include <components/tree/tree_handler.h>
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
}