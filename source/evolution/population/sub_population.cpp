#include <evolution/population/sub_population.h>
#include <components/tree/tree_handler.h>
#include "utils/random_utils.h"
#include <vector>
#include "metrics/r2.h"
#include "utils/array_utils.h"
#include "central_units/individual_infos.h"

SubPopulation::SubPopulation(int num_individual, int skill_factor, DataView dataview, int max_length, int max_depth, int max_index)
{
    this->skill_factor = skill_factor;
    this->dataview = dataview;
    this->max_length = max_length;
    this->max_depth = max_depth;

    std::vector<Individual*> individuals;
    for (int i = 0; i < num_individual; i++)
    {
        auto tree = create_tree(max_index, max_length, max_depth);
        individuals.push_back(new Individual(tree, skill_factor));
    }
    this->individuals = individuals;
    this->num_individual = num_individual;
    // hard code r2
    this->metric = new R2();
}

Individual* SubPopulation::get_random()
{
    auto idx = Random::randint<int>(0, this->individuals.size() - 1);
    return this->individuals[idx];
}

void SubPopulation::append(std::vector<Individual*> offsprings)
{
    this->individuals.insert(this->individuals.end(), offsprings.begin(), offsprings.end());
};

void SubPopulation::evaluate()
{
    for (auto ind : this->individuals)
        if (!ind->evaluated)
        {
            std::vector<float> objectives;
            auto y_hat = ind->eval(this->dataview.X_val());
            auto y_true = this->dataview.y_val();
            auto met = this->metric->call(y_true, y_hat);
            if (!this->metric->is_larger_better)
            {
                met = -met;
            }
            objectives.push_back(met);
            objectives.push_back(-ind->genes->length());
            ind->setObjective(objectives);
        }
}

std::vector<Eigen::Index> SubPopulation::get_central_ids()
{
    std::vector<Eigen::Index> ids(this->individuals.size());
    for (Eigen::Index i = 0; i < this->individuals.size(); ++i)
    {
        ids[i] = this->individuals[i]->central_id;
    }
    return ids;
};

Individual* SubPopulation::find_best_fitted_individual()
{
    auto indices = this->get_central_ids();
    Eigen::ArrayXf objective = IndividualInfos::objectives(indices, 0);
    auto best_idx = ArrayUtils::argmax <float> (objective);
    return this->individuals[best_idx];
}