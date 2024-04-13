#ifndef NODE_H
#define NODE_H

#include <Eigen/Dense>
#include <stack>
#include <string>
#include <vector>

using Eigen::ArrayXf;
using Eigen::ArrayXXf;

class Node
{
protected:
    /// @brief
    /// @param X  this is not a leaf node so it consume a vector of inputs
    /// @return
    virtual ArrayXf _eval(std::stack<ArrayXf> &X) = 0;

    /// @brief
    /// @param X this is a leaf node so it consume a matrix directly for the ease of use
    /// @return
    ArrayXf _eval(ArrayXXf X);

public:
    float weight();

    static const bool is_nonlinear = false;

    int arity;

    int index;

    int depth = -1;

    int length = -1;

    int id = -1;

    int64_t central_id = -1;

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
