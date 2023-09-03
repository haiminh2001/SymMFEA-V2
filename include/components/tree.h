#ifndef TREE_H
#define TREE_H

#include "node.h"
#include <vector>
#include <Eigen/Dense>
#include <stack>
#include <memory>
using Eigen::ArrayXXf;

class Tree{
private:
    //list of pointers of the nodes
    std::vector < Node* > nodes;
public:
    explicit Tree(std::vector<Node*> nodes);
    ArrayXXf eval(std::vector <ArrayXXf> X);
};

#endif
