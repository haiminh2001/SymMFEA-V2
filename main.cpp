
#include <iostream>
#include <Eigen/Dense>
#include <vector>
#include "components/data_utils/data_view.h"
#include "components/primitive.h"
#include "components/tree/tree_handler.h"
#include "components/tree/tree.h"
#include "evolution/population/individual.h"
#include "evolution/population/sub_population.h"
#include "components/functions/node.h"
#include "evolution/reproducer/crossover/subtree.h"
#include "central_units/individual_infos.h"
#include "central_units/id_allocator.h"
#include "utils/array_utils.h"
#include "evolution/ranker.h"
#include "evolution/selector.h"
#include "metrics/r2.h"
#include "evolution/population/population.h"
#include "evolution/algorithms/GA.h"

using namespace std;
using namespace ArrayUtils;
using Eigen::ArrayXXf;

int main()
{
    string filename = "/mnt/d/Workspace/SymMFEA/datasets/dataset_2.csv";
    auto data = readCSV(filename);
    Eigen::ArrayXf gt(data.rows());
    gt << data(Eigen::all, data.cols() - 1);

    Eigen::ArrayXXf X = data(Eigen::all, Eigen::seq(0, data.cols() - 2));

    GA algo (500, 1, 2, 100, 30, 5);

    algo.fit(X, gt);
    
}