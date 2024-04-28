#include <evolution/population/sub_population.h>
#include <components/tree/tree_handler.h>
#include "utils/random_utils.h"
#include <vector>
#include "utils/array_utils.h"
#include "central_units/individual_infos.h"
#include "thread"

/// @brief create a node on the red black tree and insert the individual
/// @param individual 
void SubPopulation::insert_individual(Individual *individual)
{
    auto node = new RedBlackTree::Node();
    node->individual = individual;
    this->individuals->insert(node);
};

/// @brief init a subpopulation with a number of random individuals
/// @param num_individual 
/// @param skill_factor 
/// @param dataview 
/// @param tree_spec 
SubPopulation::SubPopulation(int num_individual, int skill_factor, DataView dataview, TreeSpec *tree_spec)
    : tree_spec(tree_spec), dataview(dataview), skill_factor(skill_factor)
{
    this->individuals = new RedBlackTree::RedBlackTree();

    for (int i = 0; i < num_individual; i++)
    {
        this->insert_individual(new Individual(skill_factor, tree_spec));
    }
}

Individual *SubPopulation::get_random()
{
    return this->individuals->get_random_node()->individual;
}


Individual *SubPopulation::find_best_fitted_individual()
{
    return this->individuals->get_largest_node()->individual;
}



void _fit(std::vector<Individual *> individuals,
          int thread_id,
          int num_threads,
          Trainer *trainer,
          DataView dataview,
          Metric *metric)
{
    for (auto ind : individuals)
    {
        if ((!ind->evaluated) && (ind->central_id % num_threads == thread_id))
        {
            auto ind_metric = trainer->fit(ind, dataview);
            if (!metric->is_larger_better)
            {
                ind_metric = -ind_metric;
            }
            float objectives[2];
            objectives[0] = ind_metric;
            objectives[1] = (float)-(ind->genes->length());
            ind->setObjective(objectives);
        }
    }
}

void SubPopulation::evaluate(Trainer *trainer)
{
    std::vector<std::thread> threads;
    int num_threads = std::thread::hardware_concurrency();
    for (int i = 0; i < num_threads; ++i)
    {
        threads.push_back(std::thread(_fit, this->individuals, i, num_threads, trainer, this->dataview, this->metric));
    }
    for (auto &thread : threads)
    {
        thread.join();
    }
}

uint32_t SubPopulation::current_num_individuals()
{
    return this->individuals->num_nodes;
}