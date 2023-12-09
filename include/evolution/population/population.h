#ifndef SYMMFEA_POPULATION_H
#define SYMMFEA_POPULATION_H
#include "individual.h"
#include "evolution/population/sub_population.h"
#include <vector>
class Population
{
public:
    std::vector<SubPopulation*> sub_populations;
    Population(int num_tasks, int num_inviduals_per_tasks, DataPool *datapool, int max_length, int max_depth);
    void append(std::vector<std::vector<Individual*>> offsprings);
    void evaluate();
    std::vector<Individual*> find_best_fitted_individual();
};
#endif // SYMMFEA_POPULATION_H
