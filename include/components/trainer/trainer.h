#ifndef SYMMFEA_TRAINER_H
#define SYMMFEA_TRAINER_H

#include "components/trainer/trainer.h"
#include "components/trainer/loss/loss.h"
#include "components/trainer/metrics/metrics.h"
#include "evolution/population/individual.h"
#include "components/data_utils/data_view.h"
#include "components/trainer/gradient_optimizer.h"

class Trainer
{
private:
    Metric *metric;
    Loss *loss;
    GradientOptimizer *optimizer;
    int early_stopping;
    int num_steps;

public:
    Trainer(Metric *metric, Loss *loss, GradientOptimizer *optimizer, int num_steps, int early_stopping)
        : metric(metric),
          loss(loss),
          optimizer(optimizer),
          num_steps(num_steps),
          early_stopping(early_stopping){};
    float fit(Individual *individual, DataView &data);
};
#endif // SYMMFEA_TRAINER_H
