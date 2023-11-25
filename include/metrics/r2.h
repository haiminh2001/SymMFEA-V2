#ifndef SYMMFEA_R2_H
#define SYMMFEA_R2_H
#include <Eigen/Dense>
#include "metrics/metrics.h"
class R2 : public Metric
{
public:
    static const bool is_larger_better = true;
    float call(Eigen::Array<float, Eigen::Dynamic, 1> y_true, Eigen::Array<float, Eigen::Dynamic, 1> y_hat) override;
};

#endif // SYMMFEA_R2_H
