
#ifndef SYMMFEA_TREE_HANDLER_H
#define SYMMFEA_TREE_HANDLER_H
#include "tuple"
#include "tree.h"

Tree *create_tree(int max_index, int max_length, int max_depth);

std::tuple<int, int> get_possible_range(Tree tree, int point, int max_depth, int max_length);
#endif // SYMMFEA_TREE_HANDLER_H
