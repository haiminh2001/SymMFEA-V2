#include <evolution/population/sub_population.h>
#include <components/tree/tree_handler.h>
#include "utils/random_utils.h"
#include <vector>
#include "metrics/r2.h"
#include "utils/array_utils.h"
#include "central_units/individual_infos.h"
#include "thread"

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
            auto ind_metric = trainer->fit(ind, dataview, 20);
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