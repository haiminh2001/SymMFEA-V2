#ifndef NODE_H
#define NODE_H


#include <Eigen/Dense>
#include <stack>

using Eigen::ArrayXf;
using Eigen::ArrayXXf;


class Node{
public:
    static const bool is_nonlinear = false;
    int arity;
    int index;
    Node(int arity, int index);
    explicit Node(int arity);

    //if not leaf
    virtual ArrayXf eval(std::stack <ArrayXf>& X) = 0;

    //if leaf
    ArrayXf eval(ArrayXXf X) const;

    bool is_leaf() const;
};

#endif
