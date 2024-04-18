#ifndef SYMMFEA_CROSSOVER_H
#define SYMMFEA_CROSSOVER_H
#include "evolution/population/individual.h"
#include "evolution/population/sub_population.h"
#include "evolution/population/population.h"
#include "evolution/reproducer/tree_spec.h"
#include <vector>

class Crossover
{
public:
    Crossover(TreeSpec* tree_spec) : tree_spec(tree_spec) {}; 
    TreeSpec* tree_spec;
    virtual std::vector<Individual*> call(Individual* pa, Individual* pb) = 0;
    std::vector<Individual*> call(SubPopulation* supop);
    std::vector<std::vector<Individual*>> call(Population* population);
};
#endif // SYMMFEA_CROSSOVER_H
