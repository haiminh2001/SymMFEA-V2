#ifndef SYMMFEA_SUB_POPULATION_H
#define SYMMFEA_SUB_POPULATION_H
#include "evolution/population/individual.h"
#include "components/data_utils/data_view.h"
#include "components/trainer/trainer.h"
#include "components/trainer/metrics/metrics.h"
#include "evolution/reproducer/tree_spec.h"
#include "evolution/population/red_black_tree.h"

#include <vector>
#include "Eigen/Dense"

class SubPopulation
{
private:
    Metric *metric;
    TreeSpec *tree_spec;
    DataView dataview;
    RedBlackTree::RedBlackTree *individuals;

public:
    int skill_factor;
    void insert_individual(Individual *individual);
    
    uint32_t current_num_individuals();
    SubPopulation(int num_individual, int skill_factor, DataView dataview, TreeSpec *tree_spec);
    Individual *get_random();
    void append(std::vector<Individual *> offsprings);
    void evaluate(Trainer* trainer);
    Individual *find_best_fitted_individual();
    
};
#endif // SYMMFEA_SUB_POPULATION_H
