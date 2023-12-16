#include "components/trainer/trainer.h"
#include <limits>
Trainer::Trainer(Metric *metric, Loss *loss, int early_stopping)
{
    this->metric = metric;
    this->loss = loss;
    this->early_stopping = early_stopping;
}

float Trainer::fit(Individual *individual, DataView &data, int steps)
{
    auto X = data.X_train();
    auto y = data.y_train();

    int num_consecutive_not_better = 0;

    float best_objective;
    if (this->metric->is_larger_better)
        best_objective = std::numeric_limits<float>::max();
    else
        best_objective = std::numeric_limits<float>::min();

    for (int step = 0; step < steps && num_consecutive_not_better < this->early_stopping; ++step)
    {
        auto y_hat = individual->eval(X);
        auto diff = this->loss->call(y, y_hat);
        auto deltaY = std::get<0>(diff);
        auto loss = std::get<1>(diff);

        y_hat = individual->eval(data.X_val());
        auto metric = this->metric->call(data.y_val(), y_hat);

        // check if metric is getting better
        if (this->metric->is_larger_better ^ (metric > best_objective))
        {
            best_objective = metric;
            num_consecutive_not_better = 0;
        }
        else
        {
            num_consecutive_not_better++;
        }
    }
    return best_objective;
}