#include <limits>
#include "components/trainer/trainer.h"
#include "central_units/individual_infos.h"

float Trainer::fit(Individual *individual, DataView &data)
{
    auto X = data.X_train();
    auto y = data.y_train();

    auto X_val = data.X_val();
    auto y_val = data.y_val();

    int num_consecutive_not_better = 0;

    float best_objective;
    if (this->metric->is_larger_better)
        best_objective = -std::numeric_limits<float>::max();
    else
        best_objective = std::numeric_limits<float>::max();

    float metric;
    for (int step = 0; step < this->num_steps && num_consecutive_not_better < this->early_stopping; ++step)
    {
        auto y_hat = individual->forward(X);
        auto diff = this->loss->call(y, y_hat);
        auto deltaY = std::get<0>(diff);
        auto loss = std::get<1>(diff);

        // if backprop return true, it means that the deltaW is nan then we should stop training
        if (this->optimizer->backprop(individual, deltaY))
            break;

        y_hat = individual->forward(X_val, false);
        metric = this->metric->call(y_val, y_hat);

        // check if metric is getting better
        if (!(this->metric->is_larger_better ^ (metric > best_objective)))
        {
            best_objective = metric;
            num_consecutive_not_better = 0;
            IndividualInfos::weightCheckpoint.row(individual->central_id) = IndividualInfos::weight.row(individual->central_id);
        }
        else
        {
            num_consecutive_not_better++;
        }
    }

    // rollback to best checkpoint
    IndividualInfos::weight.row(individual->central_id) = IndividualInfos::weightCheckpoint.row(individual->central_id);
    return metric;
}