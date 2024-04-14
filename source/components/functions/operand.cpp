#include "components/functions/operand.h"
#include <exception>
Operand::Operand(int index) : Node(0, index)
{
    this->symbol = std::string("x_") + std::to_string(this->index);
}

ArrayXf Operand::_eval(ArrayXXf X)
{
    auto result = X.col(this->index);
    return result;
}

Node *Operand::clone()
{
    Operand *new_node = new Operand(this->index);
    return new_node;
}