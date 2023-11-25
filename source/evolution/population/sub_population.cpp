#include <evolution/population/sub_population.h>
#include <components/tree/tree_handler.h>
#include "utils/random_utils.h"
#include <vector>
#include "metrics/r2.h"

SubPopulation::SubPopulation(int num_individual, int skill_factor, DataView dataview)
{
    this->skill_factor = skill_factor;
    this->dataview = dataview;

    std::vector<Individual> individuals;
    for (int i = 0; i < num_individual; i++)
    {
        auto tree = create_tree(1, 5, 5);
        individuals.emplace_back(Individual(tree, skill_factor));
    }
    this->individuals = individuals;
    this->num_individual = num_individual;
    // hard code r2
    this->metric = new R2();
}

Individual SubPopulation::get_random()
{
    auto idx = Random::randint<int>(0, this->individuals.size() - 1);
    return this->individuals[idx];
}

void SubPopulation::append(std::vector<Individual> offsprings)
{
    this->individuals.insert(this->individuals.end(), offsprings.begin(), offsprings.end());
};

void SubPopulation::evaluate()
{
    for (auto ind : this->individuals)
        if (!ind.evaluated)
        {
            std::vector<float> objectives;
            auto y_hat = ind.eval(this->dataview.X_val());
            auto y_true = this->dataview.y_val();
            auto met = this->metric->call(y_true, y_hat);
            if (!this->metric->is_larger_better)
            {
                met = -met;
            }
            objectives.push_back(met);
            objectives.push_back(-ind.genes->length());
            ind.setObjective(objectives);
        }
}