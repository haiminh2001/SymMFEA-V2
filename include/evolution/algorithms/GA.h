#ifndef SYMMFEA_GA_H
#define SYMMFEA_GA_H

#include "evolution/reproducer/reproducing_controller.h"
#include "utils/progress_bar.h"
#include "utils/mutex.h"
#include "components/trainer/gradient_optimizer.h"
#include "components/trainer/loss/loss.h"
#include "components/trainer/trainer.h"

#include "Eigen/Dense"

#include <vector>

class GA
{
private:
    uint64_t num_concurrent_inviduals_per_tasks;
    int num_tasks;
    std::vector<int> max_length;
    std::vector<int> max_depth;
    uint32_t num_generations;
    int num_inits;

public:
    MutexUtils::MutexObject<int64_t> *quota;
    ProgressBar *progress_bar;
    ReproducingController *reproducing_controller;
    Trainer *trainer;

    GA(int64_t num_solutions,
       uint64_t num_concurrent_inviduals_per_tasks,
       int num_tasks,
       std::vector<int> max_length,
       std::vector<int> max_depth,
       Metric *metric,
       Loss *loss,
       int num_inits = 1,
       int epochs = 2,
       float learning_rate = 0.1,
       int early_stopping = 3,
       int batch_size = 512);

    void fit(Eigen::ArrayXXf X, Eigen::ArrayXf y);
};
#endif // SYMMFEA_GA_H
