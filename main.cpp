
#include <iostream>
#include <Eigen/Dense>
#include <vector>
#include "components/DataUtils/data_view.h"
#include "components/primitive.h"
#include "components/tree/tree_handler.h"
#include "components/tree/tree.h"
#include "evolution/population/individual.h"
#include "evolution/population/sub_population.h"

using namespace std;

using Eigen::ArrayXXf;

int main()
{

    ArrayXXf input(3, 2);
    input << 1, 2,
        3, 4,
        5, 6;
    ArrayXf y(3);
    y << 1, 5, 9;

    auto s = SubPopulation(5, 0);

    auto i = s.individuals[0];

    auto tree = i.genes;

    for (auto node : tree->nodes){
        cout<<node->symbol<<" "<<node->arity<<endl;
    }

    ArrayXf output = i.eval(input);
    std::cout << "input:" << std::endl
              << input << std::endl;
    std::cout << "output:" << std::endl
              << output << std::endl;

    // DataPool dp = DataPool(input, y, 0.5);
    // DataView dv = DataView(&dp, 1);
    // std::cout << dp.X_train << std::endl;
    // std::cout << dv.X_train() << std::endl;
}