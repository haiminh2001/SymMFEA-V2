
#include <iostream>
#include <Eigen/Dense>
#include <vector>

#include "utils/array_utils.h"
#include "evolution/algorithms/GA.h"
#include "components/trainer/metrics/r2.h"
#include "components/trainer/loss/mse.h"

using namespace std;
using namespace ArrayUtils;
using Eigen::ArrayXXf;

int main()
{
    string filename = "/mnt/d/Workspace/SymMFEA/datasets/dataset_2.csv";
    Eigen::ArrayXXf data = readCSV(filename);
    Eigen::ArrayXf ground_truth(data.rows());
    ground_truth << data(Eigen::all, data.cols() - 1);

    Eigen::ArrayXXf X = data(Eigen::all, Eigen::seq(0, data.cols() - 2));

    GA algo(50000, // num_solutions
            100,  // num_concurrent_inviduals_per_tasks
            1,   // num_tasks
            2,   // num_objectives
            30,  // max_length
            6,   // max_depth
            new R2(),
            new MSELoss(),
            20,   // epochs
            0.1 // learning_rate
    );

    algo.fit(X, ground_truth);
}