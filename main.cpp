
#include <iostream>
#include <Eigen/Dense>
#include <vector>
#include "components/DataUtils/data_view.h"
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

using namespace std;

using Eigen::ArrayXXf;

int main()
{
    int max_ind = 10;
    ArrayXXf input(3, 2);
    input << 1, 2,
        5, 6,
        3, 4;
    ArrayXf y(3);
    y << 1, 5, 9;

    IdAllocator::init(max_ind);
    IndividualInfos::init(max_ind, 10);

    auto s = SubPopulation(5, 0);

    auto i1 = s.individuals[0];
    auto i2 = s.individuals[1];

    auto crossover = SubTreeCrossover(5, 5);
    auto c = crossover.call(i1, i2)[0];

    cout << i1;
    cout << i2;
    cout << c;

    ArrayXf output = i1.eval(input);
    cout << "input:" << endl
         << input << endl;
    cout << "output:" << endl
         << output << endl;

    auto order = argsort<float>(output);
    for (auto i : order)
    {
        cout << "order: " << static_cast<int>(i);
    }

    // DataPool dp = DataPool(input, y, 0.5);
    // DataView dv = DataView(&dp, 1);
    // cout << dp.X_train << endl;
    // cout << dv.X_train() << endl;
}