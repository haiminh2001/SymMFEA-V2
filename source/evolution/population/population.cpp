#include "evolution/population/population.h"
#include "components/data_utils/data_view.h"
#include "components/data_utils/data_pool.h"

Population::Population(int num_tasks,
                       int num_individuals_per_tasks,
                       DataPool *datapool,
                       std::vector<TreeSpec *> tree_specs)
{
    for (int i = 0; i < num_tasks; ++i)
    {
        DataView *dv = new DataView(datapool, 1);
        this->sub_populations.push_back(new SubPopulation(num_individuals_per_tasks,
                                                          i,
                                                          dv,
                                                          tree_specs[i]));
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

void Population::get_random_subpopulations(SubPopulation **subpop_a, SubPopulation **subpop_b)
{
    // NOTE: implement this function
    *subpop_a = this->sub_populations[0];
    *subpop_b = this->sub_populations[0];
}