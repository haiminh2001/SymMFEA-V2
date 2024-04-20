#ifndef SYMMFEA_GA_H
#define SYMMFEA_GA_H
#include "Eigen/Dense"
#include "evolution/reproducer/variant.h"
#include "evolution/selector.h"
#include "evolution/ranker.h"
#include "utils/progress_bar.h"
#include "components/trainer/gradient_optimizer.h"
#include "components/trainer/loss/loss.h"
#include "components/trainer/trainer.h"

class GA
{
private:
    int num_inviduals_per_tasks;
    int num_objectives;
    int num_tasks;
    int max_length;
    int max_depth;
    int num_generations;
    ProgressBar *progress_bar;
    Variant *variant;
    Selector *selector;
    Ranker *ranker;
    Trainer *trainer;

public:
    GA(int num_inviduals_per_tasks,
       int num_tasks,
       int num_objectives,
       int num_generations,
       int max_length,
       int max_depth,
       Metric *metric,
       Loss *loss,
       int num_steps = 20,
       float learning_rate = 0.1,
       int early_stopping = 5,
       float survive_ratio = 0.33);
    void fit(Eigen::ArrayXXf X, Eigen::ArrayXf y);
    void exec_one_generation(int generation, Population* population);
};
#endif // SYMMFEA_GA_H
