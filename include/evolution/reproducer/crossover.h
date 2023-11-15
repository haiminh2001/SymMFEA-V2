#ifndef SYMMFEA_CROSSOVER_H
#define SYMMFEA_CROSSOVER_H
#include "evolution/population/individual.h"
#include <vector>
class Crossover
{
public:
    Crossover(int max_length, int max_depth);
    int max_length;
    int max_depth;
    virtual std::vector<Individual> call(Individual& pa, Individual& pb) = 0;
};
#endif // SYMMFEA_CROSSOVER_H
