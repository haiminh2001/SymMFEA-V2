#ifndef SYMMFEA_POPULATION_H
#define SYMMFEA_POPULATION_H
#include "individual.h"
#include "evolution/population/sub_population.h"
#include "components/trainer/trainer.h"
#include "evolution/reproducer/tree_spec.h"

class Population
{
public:
    std::vector<SubPopulation*> sub_populations;
    Population(int num_tasks, int num_inviduals_per_tasks, DataPool *datapool, TreeSpec* tree_spec);
    void append(std::vector<std::vector<Individual*>> offsprings);
    void evaluate(Trainer* trainer);
    std::vector<Individual*> find_best_fitted_individual();
};
#endif // SYMMFEA_POPULATION_H
