#include <Eigen/Dense>
using Eigen::MatrixXf;


class Node{
    public:
        static const bool is_nonlinear = false;
        int arity;
        int index;
        Node(int arity, int index);
        virtual float eval(MatrixXf X) = 0;

};