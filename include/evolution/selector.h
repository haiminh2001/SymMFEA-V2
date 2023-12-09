#ifndef SYMMFEA_SELECTOR_H
#define SYMMFEA_SELECTOR_H

#include "evolution/population/sub_population.h"
#include "Eigen/Dense"

class Selector
{
private:
    float survive_ratio;

public:
    void call(SubPopulation *subpop, Eigen::Array<unsigned long, Eigen::Dynamic, 1> argpos);
    Selector(float survive_ratio);
};

#endif // SYMMFEA_SELECTOR_H
