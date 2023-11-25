#include "evolution/algorithms/GA.h"
#include "central_units/id_allocator.h"
#include "central_units/individual_infos.h"
#include "evolution/population/population.h"
#include "components/data_utils/data_pool.h"
#include "evolution/reproducer/crossover/subtree.h"

GA::GA(int num_inviduals_per_tasks,
       int num_tasks,
       int num_objectives,
       int num_generations,
       int max_length,
       int max_depth,
       float survive_ratio)
{
    int max_num_individuals = num_inviduals_per_tasks * num_objectives * 2;
    this->num_tasks = num_tasks;
    IdAllocator::init(max_num_individuals);
    IndividualInfos::init(max_num_individuals, num_objectives);

    this->crossover = new SubTreeCrossover(max_length, max_depth);
    this->selector = new Selector(survive_ratio);
    this->ranker = new Ranker();

    this->num_inviduals_per_tasks = num_inviduals_per_tasks;
    this->num_objectives = num_objectives;
    this->num_generations = num_generations;

    this->progress_bar = new ProgressBar(this->num_generations);
}

void GA::fit(Eigen::ArrayXXf X, Eigen::ArrayXf y)
{
    Population population(this->num_tasks, this->num_inviduals_per_tasks, new DataPool(X, y, 0.2));
    for (int generation = 0; generation < this->num_generations; ++generation)
    {
        this->exec_one_generation(generation, population);
        this->progress_bar->updateProgress(1, population.find_best_fitted_individual());
    }
}

void GA::exec_one_generation(int generation, Population population)
{
    auto offsprings = this->crossover->call(population = population);

    population.append(offsprings);

    population.evaluate();

    for (auto subpop : population.sub_populations)
    {
        auto argpos = this->ranker->call(subpop);
        this->selector->call(subpop, argpos);
    }
}
