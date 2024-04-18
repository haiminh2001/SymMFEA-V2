
#ifndef SYMMFEA_TREE_HANDLER_H
#define SYMMFEA_TREE_HANDLER_H
#include "tuple"
#include <vector>

#include "components/functions/node.h"
#include "evolution/reproducer/tree_spec.h"

/// @brief return a vector of Node*, the nodes are sorted in the postfix order
/// @param tree_spec
/// @return
namespace TreeHandler
{
    std::vector<Node *> create_tree(TreeSpec *tree_spec);

    std::tuple<int, int> get_possible_range(Tree *tree, int point, int max_depth, int max_length);

    /// @brief each node in the vector will be cloned, the weight will be copied from the weight vector
    /// @param nodes 
    /// @param weight 
    void copy_nodes_with_weight(std::vector<Node *>* nodes, std::vector<float>* weight);
}
#endif // SYMMFEA_TREE_HANDLER_H
