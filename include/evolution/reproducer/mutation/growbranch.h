#ifndef SYMMFEA_GROWBRANCH_H
#define SYMMFEA_GROWBRANCH_H
#include "evolution/reproducer/mutation.h"
class GrowBranchMutation : public Mutation
{
public:
    std::vector<IndividualPtr> call(IndividualPtr parent, TreeSpec* tree_spec) override;
};

#endif // SYMMFEA_GROWBRANCH_H
