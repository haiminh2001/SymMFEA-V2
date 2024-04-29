#ifndef SYMMFEA_POPULATION_H
#define SYMMFEA_POPULATION_H
#include "individual.h"
#include "evolution/population/sub_population.h"
#include "components/trainer/trainer.h"
#include "evolution/reproducer/tree_spec.h"

class Population
{
public:
    std::vector<SubPopulation *> sub_populations;
    Population(int num_tasks, int num_inviduals_per_tasks, DataPool *datapool, TreeSpec *tree_spec);
    std::vector<std::shared_ptr<Individual>> find_best_fitted_individual(std::vector<std::vector<float>> *return_objectives);
    void get_random_subpopulations(SubPopulation **subpop_a, SubPopulation **subpop_b);
};
#endif // SYMMFEA_POPULATION_H
