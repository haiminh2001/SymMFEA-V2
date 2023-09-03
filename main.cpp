
#include "tree.h"
#include "product.h"
#include <iostream>
#include <Eigen/Dense>
#include <vector>
using Eigen::ArrayXXf;

int main(){
    ArrayXXf m(2,2);
    m(0,0) = 1;
    m(1,0) = 2;
    m(0,1) = 3;
    m(1,1) = 4;
    Product node = Product(2);
    Tree t = Tree(std::vector< Node* > { &node });


    ArrayXXf n = t.eval(std::vector <ArrayXXf> {m, m} );
    std::cout <<n<< std::endl;
}