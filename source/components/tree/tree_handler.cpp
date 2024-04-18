#include "vector"
#include "tuple"
#include "components/tree/tree.h"
#include "components/tree/tree_handler.h"
#include "components/primitive.h"
#include "utils/random_utils.h"

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

std::vector<Node *> TreeHandler::create_tree(TreeSpec *tree_spec)
{
    Primitive primitives = Primitive(tree_spec->usable_indices);
    int max_depth = tree_spec->max_depth;
    int max_length = tree_spec->max_length;

    std::vector<Node *> nodes;

    int a_max = max_length - 1;

    auto arity_max = max_length - 1;
    assert(arity_max >= 0);
    auto arity_min = std::min(0, arity_max);

    auto root = primitives.sampleNode(arity_min, arity_max);

    if (root->arity == 0)
    {
        return std::vector<Node *>({root});
    }

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

    return postfix;
}

/// @brief Get the maximum length and depth of a branch that can be replaced with the current branch of the given point
/// @param tree
/// @param point
/// @param max_depth
/// @param max_length
/// @return a tuple with the first element is the maximum length and the second element is the maximum depth
std::tuple<int, int> TreeHandler::get_possible_range(Tree *tree, int point, int max_depth, int max_length)
{
    int tar_depth = tree->nodes[point]->depth;
    int tar_level = tree->depth() - tar_depth;
    max_depth -= tar_level;

    int tar_length = tree->nodes[point]->length;
    int tar_remain_length = tree->length() - tar_length;
    max_length -= tar_remain_length;

    // + 1 for max_length to include the node itself
    return std::make_tuple(max_length + 1, max_depth);
}

void TreeHandler::copy_nodes_with_weight(std::vector<Node *> *nodes, std::vector<float> *weight)
{

    for (int i = 0; i < (*nodes).size(); ++i)
    {
        // if the node is registered to atree
        if ((*nodes)[i]->central_id != -1)
        {
            (*weight).push_back((*nodes)[i]->weight());
            (*nodes).at(i) = (*nodes)[i]->clone();
        }
        else
        {
            (*weight).push_back(Random::randnorm(float(0), (float)(*nodes).size()));
        }
    }
}