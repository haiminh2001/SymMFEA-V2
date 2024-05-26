#ifndef SYMMFEA_SUBTREE_H
#define SYMMFEA_SUBTREE_H
#include "evolution/reproducer/crossover.h"
class SubTreeCrossover : public Crossover
{
public:
    std::vector<IndividualPtr> call(IndividualPtr pa, IndividualPtr pb, TreeSpec* tree_spec) override;
};

#endif // SYMMFEA_SUBTREE_H
