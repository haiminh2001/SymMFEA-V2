#ifndef SYMMFEA_LOSS_H
#define SYMMFEA_LOSS_H
#include "tuple"
#include "Eigen/Dense"
class Loss
{
public:
    Loss() {};
    /// @brief 
    /// @param y 
    /// @param y_hat 
    /// @return a tuple with the first element being the gradient of the loss function and the second element being the loss value 
    virtual std::tuple<Eigen::ArrayXf, float> call(Eigen::ArrayXf y, Eigen::ArrayXf y_hat) = 0;
};
#endif // SYMMFEA_LOSS_H
