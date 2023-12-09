#ifndef SYMMFEA_CROSSOVER_H
#define SYMMFEA_CROSSOVER_H
#include "evolution/population/individual.h"
#include "evolution/population/sub_population.h"
#include "evolution/population/population.h"
#include <vector>

class Crossover
{
public:
    Crossover(int max_length, int max_depth);
    int max_length;
    int max_depth;
    virtual std::vector<Individual*> call(Individual* pa, Individual* pb) = 0;
    std::vector<Individual*> call(SubPopulation* supop);
    std::vector<std::vector<Individual*>> call(Population &population);
};
#endif // SYMMFEA_CROSSOVER_H
