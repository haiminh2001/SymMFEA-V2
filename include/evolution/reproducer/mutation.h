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
    Mutation(TreeSpec* tree_spec) : tree_spec(tree_spec) {}; 
    TreeSpec* tree_spec;
    virtual std::vector<Individual*> call(Individual* parent) = 0;
};
#endif // SYMMFEA_MUTATION_H
