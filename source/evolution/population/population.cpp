#include "evolution/population/population.h"
#include "components/data_utils/data_view.h"
#include "components/data_utils/data_pool.h"

Population::Population(int num_tasks, int num_individuals_per_tasks, DataPool *datapool)
{
    for (int i = 0; i < num_tasks; ++i)
    {
        DataView dv(datapool, 1);
        this->sub_populations.emplace_back(num_individuals_per_tasks, i, dv);
    }
}

void Population::append(std::vector<std::vector<Individual*>> offsprings)
{
    for (int i = 0; i < offsprings.size(); ++i)
    {
        this->sub_populations[i].append(offsprings[i]);
    }
};
void Population::evaluate()
{
    for (auto subpop : this->sub_populations)
    {
        subpop.evaluate();
    }
}
std::vector<Individual*> Population::find_best_fitted_individual()
{
    std::vector <Individual*> bests;
    for (auto subpop : this->sub_populations){
        bests.push_back(subpop.find_best_fitted_individual());
    }
    return bests;
}