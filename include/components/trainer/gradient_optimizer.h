#ifndef SYMMFEA_GRADIENT_OPTIMIZER_H
#define SYMMFEA_GRADIENT_OPTIMIZER_H
#include "evolution/population/individual.h"
#include "Eigen/Dense"
using Eigen::ArrayXf;

class GradientOptimizer
{
private:
    float learning_rate;

public:
    GradientOptimizer(float learning_rate);
    bool backprop(std::shared_ptr<Individual> individual, ArrayXf deltaY);
    ArrayXf compute_gradient(std::shared_ptr<Individual> individual);
};
#endif // SYMMFEA_GRADIENT_OPTIMIZER_H
