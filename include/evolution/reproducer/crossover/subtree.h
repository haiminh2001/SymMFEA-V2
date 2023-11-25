#ifndef SYMMFEA_SUBTREE_H
#define SYMMFEA_SUBTREE_H
#include "evolution/reproducer/crossover.h"
class SubTreeCrossover : public Crossover
{
public:
    SubTreeCrossover(int max_length, int max_depth);
    std::vector<Individual*> call(Individual* pa, Individual* pb) override;
};

#endif // SYMMFEA_SUBTREE_H
