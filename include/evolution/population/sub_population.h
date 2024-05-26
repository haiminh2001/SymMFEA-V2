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
    RedBlackTree::RedBlackTree<IndividualPtr> *individuals;

public:
    TreeSpec *tree_spec;
    DataView *dataview;
    int skill_factor;
    void insert_individual(IndividualPtr, std::vector<float> objectives);
    uint32_t current_num_individuals();
    SubPopulation(int num_individual,
                  int skill_factor,
                  DataView *dataview,
                  TreeSpec *tree_spec);
    IndividualPtr get_random();
    RedBlackTree::IndividualNode<IndividualPtr> *find_best_fitted_individual();
    void remove_worst();
};
#endif // SYMMFEA_SUB_POPULATION_H
