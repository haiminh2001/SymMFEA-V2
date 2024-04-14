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

    std::vector<Individual *> individuals;
    for (int i = 0; i < num_individual; i++)
    {
        individuals.push_back(new Individual(skill_factor, max_index, max_length, max_depth));
    }
    this->individuals = individuals;
    this->num_individual = num_individual;
    // hard code r2
    this->metric = new R2();
}

Individual *SubPopulation::get_random()
{
    auto idx = Random::randint<int>(0, this->individuals.size() - 1);
    return this->individuals[idx];
}

void SubPopulation::append(std::vector<Individual *> offsprings)
{
    this->individuals.insert(this->individuals.end(), offsprings.begin(), offsprings.end());
};

void SubPopulation::evaluate(Trainer *trainer)
{
    for (auto ind : this->individuals)
        if (!ind->evaluated)
        {

            // NOTE: hard code train steps
            auto metric = trainer->fit(ind, this->dataview, 20);

            if (!this->metric->is_larger_better)
            {
                metric = -metric;
            }
            
            float objectives[2];
            objectives[0] = metric;
            objectives[1] = (float)-(ind->genes->length());

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

Individual *SubPopulation::find_best_fitted_individual()
{
    auto indices = this->get_central_ids();
    Eigen::ArrayXf objective = IndividualInfos::objectives(indices, 0);
    auto best_idx = ArrayUtils::argmax<float>(objective);
    return this->individuals[best_idx];
}

void SubPopulation::setIndividuals(const std::vector<Individual *> &individuals)
{
    this->individuals = individuals;
}