#ifndef SYMMFEA_GA_H
#define SYMMFEA_GA_H
#include "Eigen/Dense"
class GA
{
public:
    GA();
    void fit(Eigen::ArrayXXf X, Eigen::ArrayXf y);
    void exec_one_generation();
};
#endif // SYMMFEA_GA_H
