#ifndef SYMMFEA_RANKER_H
#define SYMMFEA_RANKER_H

#include "evolution/population/sub_population.h"
#include "central_units/individual_infos.h"
#include "vector"
#include "Eigen/Dense"

class Ranker
{
public:
    std::vector<unsigned long> call(SubPopulation subpop);
};

#endif // SYMMFEA_RANKER_H
