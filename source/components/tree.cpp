#include "tree.h"
#include <utility>
#include <vector>
#include <stack>


using Eigen::ArrayXXf;

Tree::Tree(std::vector<Node*> nodes){
    this->nodes = std::move(nodes);
}
ArrayXXf Tree::eval(std::vector <ArrayXXf> X){
    auto length = this->nodes.size();
    std::stack <ArrayXXf> Stack;

    for (int i = 0; i < length; ++i){
        auto node = this->nodes[i];

        if (node->is_leaf()){
            
        }
    }
    return X[0];
}