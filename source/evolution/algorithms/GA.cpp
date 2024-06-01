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

#include <thread>
#include <math.h>
#include <vector>
#include <algorithm>

GA::GA(int64_t num_solutions,
       uint64_t num_concurrent_inviduals_per_tasks,
       int num_tasks,
       std::vector<int> max_length,
       std::vector<int> max_depth,
       Metric *metric,
       Loss *loss,
       int num_inits,
       int epochs,
       float learning_rate,
       int early_stoppoing,
       int batch_size)
    : trainer(new Trainer(metric, loss, new GradientOptimizer(learning_rate), epochs, early_stoppoing, batch_size)),
      progress_bar(new ProgressBar(num_solutions * num_inits, 80)),
      num_tasks(num_tasks),
      max_length(max_length),
      max_depth(max_depth),
      num_concurrent_inviduals_per_tasks(num_concurrent_inviduals_per_tasks),
      num_inits(num_inits),
      quota(new MutexUtils::MutexObject<int64_t>(num_solutions * num_inits))
{
    uint64_t max_num_concurrent_num_individuals = num_concurrent_inviduals_per_tasks * num_tasks * num_inits * 2;
    IdAllocator::init(max_num_concurrent_num_individuals);
    IndividualInfos::init(max_num_concurrent_num_individuals, *std::max_element(max_length.begin(), max_length.end()));
}

void GA::fit(Eigen::ArrayXXf X, Eigen::ArrayXf y)
{
    std::vector<TreeSpec *> tree_specs;

    for (int i = 0; i < this->num_tasks; ++i)
    {
        tree_specs.push_back(new TreeSpec(X.cols(), this->max_length[i], this->max_depth[i]));
    }

    Population *population = new Population(this->num_tasks,
                                            this->num_inits,
                                            this->num_concurrent_inviduals_per_tasks,
                                            new DataPool(X, y, 0.2),
                                            tree_specs);

    // NOTE: hardcoded crossover and mutation
    auto crossover = new SubTreeCrossover();
    auto mutation = new GrowBranchMutation();

    std::vector<Mutation *> mutations = {mutation};
    std::vector<Crossover *> crossovers = {crossover};
    this->reproducing_controller = new ReproducingController(population, mutations, crossovers);

    int num_threads = std::thread::hardware_concurrency();

    std::vector<std::thread> threads;
    for (int i = 0; i < num_threads; ++i)
    {
        threads.push_back(std::thread([](Worker *worker, GA *ga, Population *population)
                                      { worker->run(ga, population); }, new Worker(i), this, population));
    }
    for (auto &thread : threads)
    {
        thread.join();
    }

    Timer::printTime();
}
