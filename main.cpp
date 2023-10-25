
#include "components/tree/tree.h"
#include "product.h"
#include "operand.h"
#include "individual.h"
#include "sum.h"
#include <iostream>
#include <Eigen/Dense>
#include <vector>
#include "data_view.h"
#include "primitive.h"
#include "components/tree/tree_handler.h"
using namespace std;

using Eigen::ArrayXXf;

int main()
{

    ArrayXXf m(3, 2);
    m << 1, 2,
        3, 4,
        5, 6;
    ArrayXf y(3);
    y << 1, 5, 9;

    auto t = create_tree(1, 5, 20);
    // t.visualize();

    for (auto node : t.nodes){
        cout<<node->symbol<<" "<<node->arity<<"\n";
    }

    Individual i = Individual(&t, 0);
    ArrayXf n = i.eval(m);
    std::cout << "m:" << m << std::endl;
    std::cout << "n:" << n << std::endl;

    // DataPool dp = DataPool(m, y, 0.5);
    // DataView dv = DataView(&dp, 1);
    // std::cout << dp.X_train << std::endl;
    // std::cout << dv.X_train() << std::endl;
}