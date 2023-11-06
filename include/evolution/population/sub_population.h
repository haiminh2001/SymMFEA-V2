#ifndef SYMMFEA_POPULATION_H
#define SYMMFEA_POPULATION_H
#include "evolution/population/individual.h"
#include <vector>
class SubPopulation
{
public:
    int skill_factor;
    std::vector<Individual> individuals;
    SubPopulation(int num_individual, int skill_factor);
};
#endif // SYMMFEA_POPULATION_H
