#include "evolution/population/population.h"
#include "components/data_utils/data_view.h"
#include "components/data_utils/data_pool.h"

Population::Population(int num_tasks, int num_individuals_per_tasks, DataPool *datapool, int max_length, int max_depth)
{
    int max_index = datapool->X_train.cols() - 1;
    for (int i = 0; i < num_tasks; ++i)
    {
        DataView dv(datapool, 1);
        this->sub_populations.push_back(new SubPopulation(num_individuals_per_tasks, i, dv, max_length, max_depth, max_index));
    }
}

void Population::append(std::vector<std::vector<Individual *>> offsprings)
{
    for (int i = 0; i < offsprings.size(); ++i)
    {
        this->sub_populations[i]->append(offsprings[i]);
    }
};
void Population::evaluate(Trainer* trainer)
{
    for (auto subpop : this->sub_populations)
    {
        subpop->evaluate(trainer);
    }
}
std::vector<Individual *> Population::find_best_fitted_individual()
{
    std::vector<Individual *> bests;
    for (auto subpop : this->sub_populations)
    {
        bests.push_back(subpop->find_best_fitted_individual());
    }
    return bests;
}