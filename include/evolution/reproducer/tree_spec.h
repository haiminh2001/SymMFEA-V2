
#ifndef SYMMFEA_TREE_SPEC_H
#define SYMMFEA_TREE_SPEC_H
#include "vector"
class TreeSpec
{
public:

    TreeSpec(std::vector<int> usable_indices, int max_length, int max_depth);
    TreeSpec(int max_indice, int max_length, int max_depth);
    TreeSpec(TreeSpec* other);
    std::vector<int> usable_indices;
    int max_length;
    int max_depth;

};
#endif // SYMMFEA_TREE_SPEC_H
