#ifndef SYMMFEA_MUTATION_H
#define SYMMFEA_MUTATION_H
#include "evolution/population/individual.h"
#include "evolution/population/sub_population.h"
#include "evolution/population/population.h"
#include "evolution/reproducer/tree_spec.h"
#include <vector>

class Mutation
{
public:
    /**
     * Performs a mutation operation on the parent individual.
     * 
     * @param parent The parent individual to mutate.
     * @param tree_spec The tree specification for the mutation operation.
     * @return A vector of mutated individuals.
     */
    virtual std::vector<IndividualPtr> call(IndividualPtr parent, TreeSpec *tree_spec) = 0;
};
#endif // SYMMFEA_MUTATION_H
