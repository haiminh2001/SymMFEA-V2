#include "components/functions/operand.h"
#include <exception>
Operand::Operand(int index) : Node(0, index)
{
    this->symbol = std::string("x_") + std::to_string(this->index);
}

ArrayXf Operand::_eval(std::stack<ArrayXf> &X)
{
    throw std::runtime_error("This function is not supposed to be called");
    //this function is not used
    // return just to satisfy signature
    return X.top();
}

Node *Operand::clone()
{
    Operand *new_node = new Operand(this->index);
    return new_node;
}