
#include <iostream>
#include <vector>
#include <random>

#include <Eigen/Dense>

#include "utils/array_utils.h"
#include "evolution/algorithms/GA.h"
#include "components/trainer/metrics/r2.h"
#include "components/trainer/loss/mse.h"

using namespace std;
using namespace ArrayUtils;
using Eigen::ArrayXXf;

int main()
{
    std::srand(42);
    string filename = "/mnt/d/Workspace/SymMFEA/datasets/dataset_2.csv";
    Eigen::ArrayXXf data = readCSV(filename);
    Eigen::ArrayXf ground_truth(data.rows());
    ground_truth << data(Eigen::all, data.cols() - 1);

    Eigen::ArrayXXf X = data(Eigen::all, Eigen::seq(0, data.cols() - 2));

    GA algo = GA(100000,                       // num_solutions
            32,                           // num_concurrent_inviduals_per_tasks
            5,                            // num_tasks
            std::vector<int>{50, 30, 10, 10, 10}, // max_length
            std::vector<int>{6, 4, 3, 3, 3},    // max_depth
            new R2(),
            new MSELoss(),
            1, // num_inits
            20, // epochs
            0.05 // learning_rate
    );

    algo.fit(X, ground_truth);
}