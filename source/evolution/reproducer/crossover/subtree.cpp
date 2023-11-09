#include "evolution/reproducer/crossover/subtree.h"
#include "utils/random_utils.h"
#include "components/tree/tree_handler.h"
std::vector<Individual> SubTreeCrossover::call(Individual pa, Individual pb)
{
    std::vector<Individual> children;
    // select cut point on target tree, make sure child not deeper or longer than maximum values
    int tar_point;
    if (pa.genes->length() < 2)
        return children;
    else if (pa.genes->length() == 2)
        tar_point = 1;
    else
        tar_point = randint<int>(1, pa.genes->length() - 1);

    auto max_sizes = get_possible_range(*pa.genes, tar_point, this->max_length, this->max_depth);
    int max_length = std::get<0>(max_sizes);
    int max_depth = std::get<1>(max_sizes);

    std::vector<int> candidates;
    for (auto node : pb.genes->nodes)
    {
        if (node->depth <= max_depth && node->length <= max_length)
        {
            candidates.push_back(node->id);
        }
    }
    int src_point = randint<int>(0, (int)candidates.size() - 1);
    src_point = candidates[src_point];

    auto tar_tree = pa.genes->split_tree(tar_point);
    auto tar_branch = std::get<0>(tar_tree);
    auto tar_root = std::get<1>(tar_tree);

    auto source_tree = pb.genes->split_tree(src_point);
    auto source_branch = std::get<0>(source_tree);
    auto source_root = std::get<1>(source_tree);

    auto tar_root1 = std::get<0>(tar_root);
    auto tar_root2 = std::get<1>(tar_root);

    std::vector<Node *> child_nodes;
    child_nodes.insert(child_nodes.end(), tar_root1.begin(), tar_root1.end());
    child_nodes.insert(child_nodes.end(), source_branch.begin(), source_branch.end());
    child_nodes.insert(child_nodes.end(), tar_root2.begin(), tar_root2.end());

    for (int i = 0; i < child_nodes.size(); ++i)
    {
        child_nodes.at(i) = child_nodes[i]->clone();
    }

    children.emplace_back(Individual(new Tree(child_nodes), pa.skill_factor));

    return children;
}
SubTreeCrossover::SubTreeCrossover(int max_length, int max_depth) : Crossover(max_length, max_depth) {}