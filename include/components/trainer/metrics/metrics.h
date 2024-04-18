#ifndef SYMMFEA_METRICS_H
#define SYMMFEA_METRICS_H
#include <Eigen/Dense>

class Metric
{
public:
    static const bool is_larger_better = true;
    virtual float call(Eigen::Array<float, Eigen::Dynamic, 1> y_true, Eigen::Array<float, Eigen::Dynamic, 1> y_hat) = 0;
};

#endif // SYMMFEA_METRICS_H
