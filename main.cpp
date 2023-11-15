
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
#include "evolution/ranker.h"
#include "evolution/selector.h"

using namespace std;

using Eigen::ArrayXXf;

int main()
{
    int max_ind = 4;
    ArrayXXf input(max_ind, 2);
    input << 5, 6,
        1, 2,
        3, 4,
        7, 8;
    ArrayXf y(max_ind);
    y << 1, 5, 9, 10;

    IdAllocator::init(max_ind);
    IndividualInfos::init(10, 10);
    IndividualInfos::objectives = input;

    auto subpop = SubPopulation(max_ind, 0);

    auto i1 = subpop.individuals[0];
    auto i2 = subpop.individuals[1];

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

    auto ranker = Ranker();
    auto selector = Selector(0.5);
    auto argpos = ranker.call(subpop);

    selector.call(subpop, argpos);

    for(auto ind : subpop.individuals){
        cout<<"haha "<<ind.central_id<<endl;
    }

    // DataPool dp = DataPool(input, y, 0.5);
    // DataView dv = DataView(&dp, 1);
    // cout << dp.X_train << endl;
    // cout << dv.X_train() << endl;
}