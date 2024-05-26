#include "utils/random_utils.h"
#include "utils/array_utils.h"
#include "evolution/population/sub_population.h"
#include "components/tree/tree_handler.h"
#include "central_units/individual_infos.h"

#include <vector>

/// @brief create a node on the red black tree and insert the individual
/// @param individual
/**
 * Inserts an individual into the subpopulation.
 *
 * @param individual The individual to be inserted.
 */
void SubPopulation::insert_individual(IndividualPtr individual)
{
    auto node = new RedBlackTree::IndividualNode<IndividualPtr>(individual);
    node->value = individual.get()->fitness_score;
    this->individuals->insert(node);
};

/// @brief init a subpopulation with a number of random individuals
/// @param num_individual
/// @param skill_factor
/// @param dataview
/// @param tree_spec
SubPopulation::SubPopulation(int num_individual, int skill_factor, DataView *dataview, TreeSpec *tree_spec)
    : tree_spec(tree_spec), dataview(dataview), skill_factor(skill_factor)
{
    this->individuals = new RedBlackTree::RedBlackTree<IndividualPtr>();

    for (int i = 0; i < num_individual; i++)
    {
        // without training, set the objective to -inf
        // may change this behaviour
        this->insert_individual(std::make_shared<Individual>(skill_factor, tree_spec));
    }
}

IndividualPtr SubPopulation::get_random()
{
    return this->individuals->get_random_node()->data;
}

RedBlackTree::IndividualNode<IndividualPtr> *SubPopulation::find_best_fitted_individual()
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