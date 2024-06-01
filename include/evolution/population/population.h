#ifndef SYMMFEA_POPULATION_H
#define SYMMFEA_POPULATION_H
#include "individual.h"
#include "evolution/population/sub_population.h"
#include "components/trainer/trainer.h"
#include "evolution/reproducer/tree_spec.h"

#include <vector>

class Population
{
public:
    int num_tasks;
    int num_inits;
    std::vector<SubPopulation *> sub_populations;
    Population(int num_tasks,
               int num_inits,
               int num_inviduals_per_tasks,
               DataPool *datapool,
               std::vector<TreeSpec *> tree_specs);
    std::vector<IndividualPtr> find_best_fitted_individual(std::vector<std::vector<float>> *return_objectives);
};
#endif // SYMMFEA_POPULATION_H
