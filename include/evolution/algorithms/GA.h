#ifndef SYMMFEA_GA_H
#define SYMMFEA_GA_H
#include "Eigen/Dense"
#include "evolution/reproducer/crossover.h"
#include "evolution/selector.h"
#include "evolution/ranker.h"

class GA
{
private:
    int num_inviduals_per_tasks;
    int num_objectives;
    int num_tasks;
    int num_generations;
    Crossover *crossover;
    Selector *selector;
    Ranker *ranker;

public:
    GA(int num_inviduals_per_tasks,
       int num_tasks,
       int num_objectives,
       int num_generations,
       int max_length,
       int max_depth,
       float survive_ratio = 0.5);
    void fit(Eigen::ArrayXXf X, Eigen::ArrayXf y);
    void exec_one_generation(int generation, Population population);
};
#endif // SYMMFEA_GA_H
