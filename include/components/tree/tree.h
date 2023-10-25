#ifndef TREE_H
#define TREE_H

#include "node.h"
#include <vector>
#include <Eigen/Dense>
#include <stack>
#include <memory>

using Eigen::ArrayXf;

class Tree
{

public:
    // list of pointers of the nodes
    std::vector<Node *> nodes;

    explicit Tree(std::vector<Node *> nodes);

    ArrayXf eval(const ArrayXXf &X);

    void updateNodeMetadata();

    int length();

    void visualize();
};

#endif
