#include "components/functions/operand.h"
Operand::Operand(int index) : Node(0, index)
{
    this->symbol = std::string("x_") + std::to_string(this->index);
}

ArrayXf Operand::eval(std::stack<ArrayXf> &X)
{
    // return just to justify signature
    return X.top();
}

Node* Operand::clone(){
    Operand* new_node = new Operand(this->index);
    return new_node;
}