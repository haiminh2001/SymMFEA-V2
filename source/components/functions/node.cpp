#include "node.h"


Node::Node(int arity, int index= -1){
    this->arity = arity;
    this->index = index;
}

bool Node::is_leaf() const{
    return this->arity == 0;
};