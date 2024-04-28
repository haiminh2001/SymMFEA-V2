#ifndef SYMMFEA_GA_H
#define SYMMFEA_GA_H
#include "Eigen/Dense"
#include "evolution/reproducer/variant.h"
#include "utils/progress_bar.h"
#include "components/trainer/gradient_optimizer.h"
#include "components/trainer/loss/loss.h"
#include "components/trainer/trainer.h"

class GA
{
private:
    uint64_t num_solutions;
    uint64_t num_concurrent_inviduals_per_tasks;
    int num_objectives;
    int num_tasks;
    int max_length;
    int max_depth;
    uint32_t num_generations;
    ProgressBar *progress_bar;
    Variant *variant;
    Trainer *trainer;

public:
    GA(
        uint64_t num_solutions,
        uint64_t num_concurrent_inviduals_per_tasks,
        int num_tasks,
        int num_objectives,
        int max_length,
        int max_depth,
        Metric *metric,
        Loss *loss,
        int epochs = 2,
        float learning_rate = 0.1,
        int early_stopping = 3,
        int batch_size = 512);
    void fit(Eigen::ArrayXXf X, Eigen::ArrayXf y);
};
#endif // SYMMFEA_GA_H
