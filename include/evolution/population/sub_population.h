#ifndef SYMMFEA_SUB_POPULATION_H
#define SYMMFEA_SUB_POPULATION_H
#include "evolution/population/individual.h"
#include "components/data_utils/data_view.h"
#include <vector>

class SubPopulation
{
public:
    int skill_factor;
    std::vector<Individual> individuals;
    DataView dataview;
    SubPopulation(int num_individual, int skill_factor, DataView dataview);

};
#endif // SYMMFEA_SUB_POPULATION_H
