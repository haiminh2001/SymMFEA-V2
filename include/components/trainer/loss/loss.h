#ifndef SYMMFEA_LOSS_H
#define SYMMFEA_LOSS_H
#include "tuple"
#include "Eigen/Dense"
class Loss
{
public:
    Loss() {};
    virtual std::tuple<Eigen::ArrayXf, float> call(Eigen::ArrayXf y, Eigen::ArrayXf y_hat) = 0;
};
#endif // SYMMFEA_LOSS_H
