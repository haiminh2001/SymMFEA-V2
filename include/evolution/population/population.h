#ifndef SYMMFEA_POPULATION_H
#define SYMMFEA_POPULATION_H
#include "individual.h"
#include <vector>
class Population{
public:
    int skill_factor;
    std::vector <Individual> individuals;
    Population(int num_individual);
};
#endif //SYMMFEA_POPULATION_H