#include "evolution/reproducer/mutation/growbranch.h"
#include "components/tree/tree_handler.h"
#include "utils/random_utils.h"
#include "vector"

std::vector<std::shared_ptr<Individual>> GrowBranchMutation::call(std::shared_ptr<Individual> parent_)
{
    auto parent = parent_.get();
    std::vector<std::shared_ptr<Individual>> children;

    // exclude the last node because if replcae the last node then the tree will be replaced entirely
    if (parent->genes->length() <= 2)
    {
        return children;
    }
    auto grow_point = Random::randint<int>(0, parent->genes->length() - 2);

    auto max_sizes = TreeHandler::get_possible_range(parent->genes, grow_point, this->tree_spec->max_depth, this->tree_spec->max_length);
    int max_length = std::get<0>(max_sizes);
    int max_depth = std::get<1>(max_sizes);

    auto branch_spec = new TreeSpec(this->tree_spec);
    branch_spec->max_length = max_length;
    branch_spec->max_depth = max_depth;

    auto branch = TreeHandler::create_tree(branch_spec);

    auto source_tree = parent->genes->split_tree(grow_point);

    auto source_root = std::get<1>(source_tree);
    auto source_root1 = std::get<0>(source_root);
    auto source_root2 = std::get<1>(source_root);

    std::vector<Node *> child_nodes;
    std::vector<float> child_weight;
    child_nodes.insert(child_nodes.end(), source_root1.begin(), source_root1.end());
    child_nodes.insert(child_nodes.end(), branch.begin(), branch.end());
    child_nodes.insert(child_nodes.end(), source_root2.begin(), source_root2.end());

    TreeHandler::copy_nodes_with_weight(&child_nodes, &child_weight);

    auto child = new Individual(child_nodes, parent->skill_factor);
    child->genes->setWeight(child_weight);
    children.push_back(std::shared_ptr<Individual>(child));
    // NOTE: add tree's size verification here
    return children;
}
