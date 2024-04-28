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
    int epochs;
    int batch_size;

public:
    Trainer(Metric *metric, Loss *loss, GradientOptimizer *optimizer, int epochs, int early_stopping, int batch_size)
        : metric(metric),
          loss(loss),
          optimizer(optimizer),
          epochs(epochs),
          early_stopping(early_stopping),
          batch_size(batch_size){};
    float fit(Individual *individual, DataView* data);
};
#endif // SYMMFEA_TRAINER_H
