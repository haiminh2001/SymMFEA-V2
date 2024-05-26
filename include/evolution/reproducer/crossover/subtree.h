#ifndef SYMMFEA_SUBTREE_H
#define SYMMFEA_SUBTREE_H
#include "evolution/reproducer/crossover.h"
class SubTreeCrossover : public Crossover
{
public:
    SubTreeCrossover(TreeSpec *tree_spec) : Crossover(tree_spec){};
    std::vector<IndividualPtr> call(IndividualPtr pa, IndividualPtr pb) override;
};

#endif // SYMMFEA_SUBTREE_H
