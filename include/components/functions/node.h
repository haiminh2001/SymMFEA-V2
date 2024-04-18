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
    virtual ArrayXf _forward(std::stack<ArrayXf> &X, bool record_gradient) { return ArrayXf(); };

    /// @brief
    /// @param X this is a leaf node so it consume a matrix directly for the ease of use
    /// @return
    virtual ArrayXf _forward(ArrayXXf X, bool record_gradient) { return ArrayXf(); };

public:
    float weight();

    static const bool is_nonlinear = false;

    int arity;

    int index;

    int depth;

    int length;

    int id;

    int64_t central_id;

    ArrayXf weightDelta;
    std::vector<ArrayXf> inputDelta;

    std::string symbol;

    bool is_leaf();

    Node();

    Node(int arity, int index);

    explicit Node(int arity);

    std::vector<ArrayXf> backprop(ArrayXf &dY);
    virtual Node *clone() = 0;
    friend std::ostream &operator<<(std::ostream &os, const Node &node);

    template <typename T>
    ArrayXf forward(T X, bool record_gradient = true);
};

#endif
