#ifndef TREE_H
#define TREE_H
#include <vector>
#include <Eigen/Dense>
#include <stack>
#include <memory>
#include <tuple>

#include "components/functions/node.h"

using Eigen::ArrayXf;

class Tree
{

public:
    // list of pointers of the nodes
    std::vector<Node *> nodes;

    explicit Tree(std::vector<Node *> nodes, int central_id);

    ArrayXf eval(const ArrayXXf &X);

    void updateNodeMetadata(int central_id);

    int length();

    int depth();

    void visualize();

    std::tuple<std::vector<Node *>, std::tuple<std::vector<Node *>, std::vector<Node *>>> split_tree(int split_point);

    friend std::ostream &operator<<(std::ostream &os, const Tree &tree);
};

#endif
