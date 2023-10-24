#ifndef NODE_H
#define NODE_H


#include <Eigen/Dense>
#include <stack>
#include <string>
using Eigen::ArrayXf;
using Eigen::ArrayXXf;


class Node{
public:
    static const bool is_nonlinear = false;

    int arity;

    int index;

    std::string symbol;

    int depth= -1;

    int length= -1;

    int id = -1;

    Node(int arity, int index);

    explicit Node(int arity);

    //if not leaf
    virtual ArrayXf eval(std::stack <ArrayXf>& X) = 0;

    //if leaf
    ArrayXf eval(ArrayXXf X) const;

    bool is_leaf();
};

#endif
