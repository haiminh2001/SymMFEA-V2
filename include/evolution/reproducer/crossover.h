#ifndef SYMMFEA_CROSSOVER_H
#define SYMMFEA_CROSSOVER_H
#include "evolution/population/individual.h"
#include "evolution/population/sub_population.h"
#include "evolution/population/population.h"
#include "evolution/reproducer/tree_spec.h"

#include <vector>
#include <memory>

class Crossover
{
public: 
  
    /**
     * Performs crossover operation between two parent individuals.
     * 
     * @param pa The first parent individual.
     * @param pb The second parent individual.
     * @param tree_spec The tree specifications of the offsprings.
     * @return A vector of offspring individuals resulting from the crossover operation.
     */
    virtual std::vector<IndividualPtr> call(IndividualPtr pa, IndividualPtr pb, TreeSpec *tree_spec) = 0;
};
#endif // SYMMFEA_CROSSOVER_H
