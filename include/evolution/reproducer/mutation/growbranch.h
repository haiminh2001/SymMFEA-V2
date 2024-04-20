#ifndef SYMMFEA_GROWBRANCH_H
#define SYMMFEA_GROWBRANCH_H
#include "evolution/reproducer/mutation.h"
class GrowBranchMutation : public Mutation
{
public:
    GrowBranchMutation(TreeSpec* tree_spec) : Mutation(tree_spec) {};
    std::vector<Individual*> call(Individual* parent) override;
};

#endif // SYMMFEA_GROWBRANCH_H