#include <Eigen/Dense>
#include <vector>
using Eigen::ArrayXXf;


class Node{
    public:
        static const bool is_nonlinear = false;
        int arity;
        int index;
        Node(int arity, int index);
        virtual ArrayXXf eval(std::vector <ArrayXXf> X) = 0;

};