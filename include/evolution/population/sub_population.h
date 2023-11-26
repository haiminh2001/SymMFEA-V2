#ifndef SYMMFEA_SUB_POPULATION_H
#define SYMMFEA_SUB_POPULATION_H
#include "evolution/population/individual.h"
#include "components/data_utils/data_view.h"
#include "metrics/metrics.h"
#include <vector>
#include "Eigen/Dense"

class SubPopulation
{
private: 
    Metric* metric;
    int max_length;
    int max_depth;
public:
    int skill_factor;
    std::vector<Individual*> individuals;
    DataView dataview;
    int num_individual;
    SubPopulation(int num_individual, int skill_factor, DataView dataview, int max_length, int max_depth, int max_index);
    Individual* get_random();
    void append(std::vector<Individual*> offsprings);
    void evaluate();
Individual* find_best_fitted_individual();
    std::vector<Eigen::Index> get_central_ids();
};
#endif // SYMMFEA_SUB_POPULATION_H
