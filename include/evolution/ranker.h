#ifndef SYMMFEA_RANKER_H
#define SYMMFEA_RANKER_H
#include "Eigen/Dense"


#include "evolution/population/sub_population.h"

class Ranker
{
public:
    Eigen::Array<unsigned long, Eigen::Dynamic, 1> call(SubPopulation* subpop);
};

#endif // SYMMFEA_RANKER_H
