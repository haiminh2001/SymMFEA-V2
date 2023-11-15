#ifndef SYMMFEA_RANKER_H
#define SYMMFEA_RANKER_H

#include "evolution/population/sub_population.h"
#include "Eigen/Dense"

class Ranker
{
public:
    Eigen::Array<unsigned long, Eigen::Dynamic, 1> call(SubPopulation& subpop);
};

#endif // SYMMFEA_RANKER_H
