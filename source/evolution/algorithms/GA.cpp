#include "evolution/algorithms/GA.h"
#include "central_units/id_allocator.h"
#include "central_units/individual_infos.h"
#include "evolution/population/population.h"
#include "components/data_utils/data_pool.h"
#include "evolution/reproducer/tree_spec.h"
#include "evolution/reproducer/crossover/subtree.h"
#include "evolution/reproducer/mutation/growbranch.h"
#include <math.h>
GA::GA(int num_inviduals_per_tasks,
       int num_tasks,
       int num_objectives,
       int num_generations,
       int max_length,
       int max_depth,
       Metric *metric,
       Loss *loss,
       int num_steps,
       float learning_rate,
       int early_stoppoing,
       float survive_ratio)
    : trainer(new Trainer(metric, loss, new GradientOptimizer(learning_rate), num_steps, early_stoppoing)),
      progress_bar(new ProgressBar(num_generations)),
      ranker(new Ranker()),
      selector(new Selector(survive_ratio)),
      num_tasks(num_tasks),
      max_length(max_length),
      max_depth(max_depth),
      num_objectives(num_objectives),
      num_generations(num_generations),
      num_inviduals_per_tasks(num_inviduals_per_tasks)
{
    
    uint64_t max_num_individuals = static_cast<uint64_t> (num_inviduals_per_tasks * num_tasks * 3);

    IdAllocator::init(max_num_individuals);
    IndividualInfos::init(max_num_individuals, num_objectives, max_length);
}

void GA::fit(Eigen::ArrayXXf X, Eigen::ArrayXf y)
{
    TreeSpec *tree_spec = new TreeSpec(X.cols(), this->max_length, this->max_depth);

    auto crossover = new SubTreeCrossover(tree_spec);
    auto mutation = new GrowBranchMutation(tree_spec); 
    this->variant = new Variant(mutation, crossover);

    Population* population = new Population(this->num_tasks, this->num_inviduals_per_tasks, new DataPool(X, y, 0.2), tree_spec);
    for (int generation = 0; generation < this->num_generations; ++generation)
    {
        this->exec_one_generation(generation, population);
        this->progress_bar->updateProgress(1, population->find_best_fitted_individual());
    }
}

void GA::exec_one_generation(int generation, Population* population)
{
    this->variant->call(population);

    population->evaluate(this->trainer);

    for (auto subpop : population->sub_populations)
    {
        // get the position of the best individuals
        auto argpos = this->ranker->call(subpop);
        this->selector->call(subpop, argpos);
    }
}
