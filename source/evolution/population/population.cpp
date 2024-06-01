#include "evolution/population/population.h"
#include "components/data_utils/data_view.h"
#include "components/data_utils/data_pool.h"

#include "iostream"
Population::Population(int num_tasks,
                       int num_inits,
                       int num_individuals_per_tasks,
                       DataPool *datapool,
                       std::vector<TreeSpec *> tree_specs) : num_inits(num_inits), num_tasks(num_tasks)
{
    for (int j = 0; j < num_inits; ++j)
    {
        for (int i = 0; i < num_tasks; ++i)
        {
            this->sub_populations.push_back(new SubPopulation(num_individuals_per_tasks,
                                                              j * num_tasks + i,
                                                              new DataView(datapool, 1),
                                                              tree_specs[i]));
        }
    }
}

std::vector<IndividualPtr> Population::find_best_fitted_individual(std::vector<std::vector<float>> *return_objectives)
{
    std::vector<IndividualPtr> bests;

    for (auto subpop : this->sub_populations)
    {
        auto node = subpop->find_best_fitted_individual();
        (*return_objectives).push_back({node->value});
        bests.push_back(node->data);
    }
    return bests;
}
