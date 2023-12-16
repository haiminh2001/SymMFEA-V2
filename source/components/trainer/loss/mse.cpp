#include "components/trainer/loss/mse.h"

std::tuple<Eigen::ArrayXf, float> MSELoss::call(Eigen::ArrayXf y, Eigen::ArrayXf y_hat)
{
    auto diff = y_hat - y;
    return std::make_tuple(2 * diff, (diff * diff).mean());
}