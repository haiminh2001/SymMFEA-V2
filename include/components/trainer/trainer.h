#ifndef SYMMFEA_TRAINER_H
#define SYMMFEA_TRAINER_H

#include "components/trainer/trainer.h"
#include "components/trainer/loss/loss.h"
#include "metrics/metrics.h"
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

public:
    Trainer(Metric *metric, Loss *loss, GradientOptimizer *optimizer, int early_stopping);
    float fit(Individual *individual, DataView &data, int steps);
};
#endif // SYMMFEA_TRAINER_H
