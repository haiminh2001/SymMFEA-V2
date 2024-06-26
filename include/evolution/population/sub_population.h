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

    RedBlackTree::RedBlackTree<std::shared_ptr<Individual>> *individuals;

public:
    DataView *dataview;
    int skill_factor;
    void insert_individual(std::shared_ptr<Individual> individual, std::vector<float> objectives);
    uint32_t current_num_individuals();
    SubPopulation(int num_individual, int skill_factor, DataView *dataview, TreeSpec *tree_spec);
    std::shared_ptr<Individual> get_random();
    RedBlackTree::IndividualNode<std::shared_ptr<Individual>> *find_best_fitted_individual();
    void remove_worst();
};
#endif // SYMMFEA_SUB_POPULATION_H
