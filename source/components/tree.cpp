#include "tree.h"
#include <utility>
#include <vector>
#include <stack>
#include <iostream>


Tree::Tree(std::vector<Node*> nodes){
    this->nodes = std::move(nodes);
}
ArrayXf Tree::eval(const ArrayXXf& X){
    auto length = this->nodes.size();
    std::stack <ArrayXf> Stack;

    for (int i = 0; i < length; ++i){
        auto node = this->nodes[i];

        ArrayXf val;

        if (node->is_leaf()){
            val = node->eval(X);
        }
        else{
            val = node->eval(Stack);
        }

        Stack.push(val);
    }

    assert(Stack.size() == 1);
    return Stack.top();

}