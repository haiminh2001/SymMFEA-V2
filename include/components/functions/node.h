#include <Eigen/Dense>
#include <vector>
using Eigen::MatrixXf;


class Node{
    public:
        static const bool is_nonlinear = false;
        int arity;
        int index;
        Node(int arity, int index);
        virtual MatrixXf eval(std::vector <MatrixXf> X) = 0;

};