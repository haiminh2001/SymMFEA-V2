#ifndef SYMMFEA_MSE_H
#define SYMMFEA_MSE_H
#include "components/trainer/loss/loss.h"
class MSELoss : public Loss
{
public:
    MSELoss() : Loss () {};
    std::tuple<Eigen::ArrayXf, float> call(Eigen::ArrayXf y, Eigen::ArrayXf y_hat) override;
};

#endif // SYMMFEA_MSE_H
