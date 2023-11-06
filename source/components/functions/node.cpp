#include "components/functions/node.h"

Node::Node(int arity, int index){
    this->arity = arity;
    this->index = index;
}

Node::Node(int arity){
    this->arity = arity;
    this->index = -1;
}

bool Node::is_leaf(){
    return this->arity == 0;
}

ArrayXf Node::eval(ArrayXXf X) const{
    assert (this->index >= 0);
    return X.col(this->index);
}

template <typename Derived>
Node* Node::copy(Node* original_node){
    auto copy_node = new Derived(static_cast<const Derived&>(original_node));
    copy_node->arity = original_node->arity;
    copy_node->index = original_node->index;
    return copy_node
}