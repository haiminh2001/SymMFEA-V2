#ifndef NODE_H
#define NODE_H

#include <Eigen/Dense>
#include <stack>
#include <string>
using Eigen::ArrayXf;
using Eigen::ArrayXXf;

class Node
{
protected:
    // if not leaf
    virtual ArrayXf _eval(std::stack<ArrayXf> &X) = 0;

    // if leaf
    ArrayXf _eval(ArrayXXf X);

    float weight();

public:
    static const bool is_nonlinear = false;

    int arity;

    int index;

    int depth = -1;

    int length = -1;

    int id = -1;

    int central_id = -1;

    ArrayXf weightDelta;
    std::vector<ArrayXf> inputDelta;

    std::string symbol;

    bool is_leaf();

    Node(int arity, int index);

    explicit Node(int arity);

    std::vector<ArrayXf> backprop(ArrayXf &dY);

    virtual Node *clone() = 0;

    friend std::ostream &operator<<(std::ostream &os, const Node &node);

    template <typename T>
    ArrayXf eval(T X);
};

#endif
