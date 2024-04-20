#ifndef SYMMFEA_SUB_POPULATION_H
#define SYMMFEA_SUB_POPULATION_H
#include "evolution/population/individual.h"
#include "components/data_utils/data_view.h"
#include "components/trainer/trainer.h"
#include "components/trainer/metrics/metrics.h"
#include "evolution/reproducer/tree_spec.h"
#include <vector>
#include "Eigen/Dense"

class SubPopulation
{
private:
    Metric *metric;
    TreeSpec *tree_spec;

public:
    int skill_factor;
    std::vector<Individual *> individuals;
    DataView dataview;
    uint32_t current_num_individuals();
    SubPopulation(int num_individual, int skill_factor, DataView dataview, TreeSpec *tree_spec);
    Individual *get_random();
    void append(std::vector<Individual *> offsprings);
    void evaluate(Trainer* trainer);
    Individual *find_best_fitted_individual();
    std::vector<Eigen::Index> get_central_ids();
    void setIndividuals(const std::vector<Individual *> &individuals);
};
#endif // SYMMFEA_SUB_POPULATION_H
