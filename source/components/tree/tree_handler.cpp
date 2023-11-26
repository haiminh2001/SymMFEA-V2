#include "vector"
#include "tuple"
#include "components/tree/tree.h"
#include "components/tree/tree_handler.h"
#include "components/primitive.h"

void fill_postfix(int cur_idx,
                  int &cur_postfix_idx,
                  std::vector<std::tuple<Node *, int, int>> ls_nodes,
                  std::vector<Node *> &postfix)
{
    auto cur_info = ls_nodes[cur_idx];
    auto cur_node = std::get<0>(cur_info);
    auto firstChildIndex = std::get<2>(cur_info);
    cur_postfix_idx -= 1;
    postfix[cur_postfix_idx] = cur_node;

    if (cur_node->is_leaf())
        return;

    assert(firstChildIndex != -1);

    for (int i = firstChildIndex; i < firstChildIndex + cur_node->arity; ++i)
    {
        fill_postfix(i, cur_postfix_idx, ls_nodes, postfix);
    }
}

Tree* create_tree(int max_index, int max_length, int max_depth)
{
    Primitive primitives = Primitive(max_index = max_index);
    std::vector<Node *> nodes;

    int a_max = max_length - 1;

    auto root = primitives.sampleNode(1, max_length - 1);

    int num_open_nodes = root->arity;
    std::vector<std::tuple<Node *, int, int>> ls_nodes; //  list of tuple node, depth, first child index

    ls_nodes.emplace_back(root, 0, -1);

    for (int i = 0; i < max_length; i++)
    {

        if (num_open_nodes == 0)
            break;

        auto &cur_info = ls_nodes[i];
        auto cur_node = std::get<0>(cur_info);

        if (!cur_node->is_leaf())
        {

            auto cur_node_depth = std::get<1>(cur_info) + 1;

            int cur_num_nodes = static_cast<int>(ls_nodes.size());
            std::get<2>(cur_info) = cur_num_nodes;

            for (int j = 0; j < cur_node->arity; ++j)
            {
                int cur_a_max, cur_a_min;
                if (cur_node_depth < max_depth - 1)
                    cur_a_max = std::min(a_max, max_length - i - 1 - num_open_nodes);
                else
                    cur_a_max = 0;

                if (num_open_nodes < 1)
                    cur_a_min = 0;

                else
                    cur_a_min = std::min(1, cur_a_max);

                auto child_node = primitives.sampleNode(cur_a_min, cur_a_max);

                assert(child_node->arity >= cur_a_min);
                assert(child_node->arity <= cur_a_max);

                ls_nodes.emplace_back(child_node, cur_node_depth, -1);
                num_open_nodes += child_node->arity;
            }
        }
        num_open_nodes -= 1;
    }

    assert(num_open_nodes == 0);

    int num_nodes = (int)ls_nodes.size();
    std::vector<Node *> postfix(num_nodes, nullptr);

    fill_postfix(0, num_nodes, ls_nodes, postfix);

    Tree* tree = new Tree(postfix);
    
    return tree;
}

std::tuple<int, int> get_possible_range(Tree tree, int point, int max_depth, int max_length){
    int tar_depth = tree.nodes[point]->depth;
    int tar_level = tree.depth() - tar_depth;
    max_depth = max_depth - tar_level;
    int tar_length  = tree.nodes[point]->length;
    int tar_remain_length = tree.length() - tar_length;
    max_length = max_length - tar_remain_length;
    return std::make_tuple(max_length, max_depth);
}