
#include "tree.h"
#include "product.h"
#include "operand.h"
#include "sum.h"
#include <iostream>
#include <Eigen/Dense>
#include <vector>
using Eigen::ArrayXXf;

int main(){
    ArrayXXf m(3,2);
    m(0,0) = 1;
    m(1,0) = 2;
    m(0,1) = 3;
    m(1,1) = 4;
    m(2, 0) = 5;
    m(2, 1) = 10;
    Product node = Product(2);
    Sum sum = Sum(2);
    Operand o1 = Operand(0);
    Operand o2 = Operand(1);


    Tree t = Tree(std::vector< Node* > {&o1, &o2, &node, &o1, &sum});

    ArrayXf n = t.eval(m);
    std::cout<<"m:" <<m<< std::endl;
    std::cout<<"n:" <<n<< std::endl;
}