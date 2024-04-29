#include "evolution/reproducer/crossover/subtree.h"
#include "utils/random_utils.h"
#include "components/tree/tree_handler.h"
std::vector<std::shared_ptr<Individual>> SubTreeCrossover::call(std::shared_ptr<Individual> pa_, std::shared_ptr<Individual> pb_)
{
    auto pa = pa_.get();
    auto pb = pb_.get();

    std::vector<std::shared_ptr<Individual>> children;
    // select the cut point on the target tree, make sure the child will not be deeper or longer than the maximum values
    int tar_point;
    if (pa->genes->length() < 2)
    {
        return children;
    }

    else if (pa->genes->length() == 2)
        tar_point = 1;
    else
        tar_point = Random::randint<int>(1, pa->genes->length() - 2);

    auto max_sizes = TreeHandler::get_possible_range(pa->genes, tar_point, this->tree_spec->max_depth, this->tree_spec->max_length);
    int max_length = std::get<0>(max_sizes);
    int max_depth = std::get<1>(max_sizes);

    std::vector<int> candidates;
    for (auto node : pb->genes->nodes)
    {
        if (node->depth <= max_depth && (node->length + 1) <= max_length)
        {
            candidates.push_back(node->id);
        }
    }

    if (candidates.size() == 0)
        return children;

    int src_point = Random::randint<int>(0, (int)candidates.size() - 1);
    src_point = candidates[src_point];

    auto tar_tree = pa->genes->split_tree(tar_point);
    auto tar_branch = std::get<0>(tar_tree);
    auto tar_root = std::get<1>(tar_tree);

    auto source_tree = pb->genes->split_tree(src_point);
    auto source_branch = std::get<0>(source_tree);
    auto source_root = std::get<1>(source_tree);

    auto tar_root1 = std::get<0>(tar_root);
    auto tar_root2 = std::get<1>(tar_root);

    std::vector<Node *> child_nodes;
    std::vector<float> child_weight;
    child_nodes.insert(child_nodes.end(), tar_root1.begin(), tar_root1.end());
    child_nodes.insert(child_nodes.end(), source_branch.begin(), source_branch.end());
    child_nodes.insert(child_nodes.end(), tar_root2.begin(), tar_root2.end());

    TreeHandler::copy_nodes_with_weight(&child_nodes, &child_weight);

    std::shared_ptr<Individual> child = std::make_shared<Individual>(child_nodes, pa->skill_factor);
    child->genes->setWeight(child_weight);
    children.push_back(child);

    // NOTE: add tree's size verification here
    return children;
}
