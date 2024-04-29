#include "evolution/population/sub_population.h"
#include "components/tree/tree_handler.h"
#include "utils/random_utils.h"
#include "utils/array_utils.h"
#include "central_units/individual_infos.h"

#include <limits>
#include <vector>

/// @brief create a node on the red black tree and insert the individual
/// @param individual
void SubPopulation::insert_individual(std::shared_ptr<Individual> individual, std::vector<float> objectives)
{
    auto node = new RedBlackTree::IndividualNode(individual);
    this->individuals->insert(node);

    // NOTE: may reimplement the value of the individual
    node->value = objectives[0];
};

/// @brief init a subpopulation with a number of random individuals
/// @param num_individual
/// @param skill_factor
/// @param dataview
/// @param tree_spec
SubPopulation::SubPopulation(int num_individual, int skill_factor, DataView *dataview, TreeSpec *tree_spec)
    : tree_spec(tree_spec), dataview(dataview), skill_factor(skill_factor)
{
    this->individuals = new RedBlackTree::RedBlackTree();

    for (int i = 0; i < num_individual; i++)
    {
        // without training, set the objective to -inf
        // may change this behaviour
        this->insert_individual(std::make_shared<Individual>(skill_factor, tree_spec),
                                {-std::numeric_limits<float>::max()});
    }
}

std::shared_ptr<Individual> SubPopulation::get_random()
{
    return this->individuals->get_random_node()->individual;
}

RedBlackTree::IndividualNode *SubPopulation::find_best_fitted_individual()
{
    return this->individuals->get_largest_node();
}

uint32_t SubPopulation::current_num_individuals()
{
    return this->individuals->num_nodes;
}
void SubPopulation::remove_worst()
{
    this->individuals->remove_smallest_node();
}