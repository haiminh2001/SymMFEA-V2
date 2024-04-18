#include "components/trainer/metrics/r2.h"

float R2::call(Eigen::Array<float, Eigen::Dynamic, 1> y_true, Eigen::Array<float, Eigen::Dynamic, 1> y_hat)
{
    auto tss = (y_true.array() - y_true.mean()).square().sum();
    auto rss = (y_true - y_hat).square().sum();
    return 1.0 - rss / tss;
}