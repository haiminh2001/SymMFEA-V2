#include "sum.h"
#include <iostream>
#include <Eigen/Dense>
#include <vector>
using Eigen::MatrixXf;

int main(){
    MatrixXf m(2,2);
    m(0,0) = 3;
    m(1,0) = 2.5;
    m(0,1) = -1;
    m(1,1) = m(1,0) + m(0,1);
    Sum node = Sum(2,1);
    MatrixXf n = node.eval(std::vector <MatrixXf> {m, m} );
    std::cout << n << std::endl;
}