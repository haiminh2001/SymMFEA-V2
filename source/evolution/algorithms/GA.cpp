#include "evolution/algorithms/GA.h"
#include "central_units/id_allocator.h"
#include "central_units/individual_infos.h"
#include "evolution/population/population.h"
#include "components/data_utils/data_pool.h"
#include "evolution/reproducer/tree_spec.h"
#include "evolution/reproducer/crossover/subtree.h"
#include "evolution/reproducer/mutation/growbranch.h"
#include "evolution/algorithms/worker.h"
#include "utils/timer.h"
#include "utils/mutex.h"

#include "thread"
#include <math.h>
GA::GA(int64_t num_solutions,
       uint64_t num_concurrent_inviduals_per_tasks,
       int num_tasks,
       int num_objectives,
       int max_length,
       int max_depth,
       Metric *metric,
       Loss *loss,
       int epochs,
       float learning_rate,
       int early_stoppoing,
       int batch_size)
    : trainer(new Trainer(metric, loss, new GradientOptimizer(learning_rate), epochs, early_stoppoing, batch_size)),
      progress_bar(new ProgressBar(num_concurrent_inviduals_per_tasks, 80)),
      num_tasks(num_tasks),
      max_length(max_length),
      max_depth(max_depth),
      num_objectives(num_objectives),
      num_concurrent_inviduals_per_tasks(num_concurrent_inviduals_per_tasks),
      quota(new MutexUtils::MutexObject<int64_t>(num_solutions))
{
    uint64_t max_num_concurrent_num_individuals = num_concurrent_inviduals_per_tasks * num_tasks * 2;
    IdAllocator::init(max_num_concurrent_num_individuals);
    IndividualInfos::init(max_num_concurrent_num_individuals, num_objectives, max_length);
}

void GA::fit(Eigen::ArrayXXf X, Eigen::ArrayXf y)
{
    TreeSpec *tree_spec = new TreeSpec(X.cols(), this->max_length, this->max_depth);

    auto crossover = new SubTreeCrossover(tree_spec);
    auto mutation = new GrowBranchMutation(tree_spec);
    this->variant = new Variant(mutation, crossover);

    Population *population = new Population(this->num_tasks, this->num_concurrent_inviduals_per_tasks, new DataPool(X, y, 0.2), tree_spec);

    int num_threads = std::thread::hardware_concurrency();

    std::vector<std::thread> threads;
    for (int i = 0; i < num_threads; ++i)
    {
        Worker *worker = new Worker();
        threads.push_back(std::thread([](Worker *worker, GA *ga, Population *population)
                                      { worker->run(ga, population); },
                                      worker, this, population));
    }
    for (auto &thread : threads)
    {
        thread.join();
    }

    Timer::printTime();
}

// void GA::exec_one_generation(uint32_t generation, Population *population)
// {
//     Timer::startTimer();
//     this->variant->call(population);
//     Timer::logTime("Variation");

//     Timer::startTimer();
//     population->evaluate(this->trainer);
//     Timer::logTime("Evaluation");

//     Timer::startTimer();
//     for (auto subpop : population->sub_populations)
//     {
//         // get the position of the best individuals
//         auto argpos = this->ranker->call(subpop);
//         this->selector->call(subpop, argpos, generation);
//     }
//     Timer::logTime("Selection");
// }
