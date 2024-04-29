#ifndef SYMMFEA_VARIANT_H
#define SYMMFEA_VARIANT_H
#include "evolution/population/individual.h"
#include "evolution/population/population.h"
#include "evolution/reproducer/mutation.h"
#include "evolution/reproducer/crossover.h"
#include <vector>

class Variant
{
public:
    Variant(Mutation* mutation, Crossover* crossover) : mutation(mutation), crossover(crossover) {}; 
    Mutation* mutation;
    Crossover* crossover;
    
    std::vector<std::shared_ptr<Individual>> call(Population* popluation);
};
#endif // SYMMFEA_VARIANT_H
