#ifndef SYMMFEA_SUBTREE_H
#define SYMMFEA_SUBTREE_H
#include "evolution/reproducer/crossover.h"
class SubTreeCrossover : public Crossover
{
public:
    SubTreeCrossover(TreeSpec *tree_spec) : Crossover(tree_spec){};
    std::vector<std::shared_ptr<Individual>> call(std::shared_ptr<Individual> pa, std::shared_ptr<Individual> pb) override;
};

#endif // SYMMFEA_SUBTREE_H
