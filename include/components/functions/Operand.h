#ifndef SYMMFEA_OPERAND_H
#define SYMMFEA_OPERAND_H

#include "node.h"

class Operand : public Node{
public:
    explicit Operand(int index);
    Node * clone() override;

private:
    ArrayXf _forward(ArrayXXf X, bool record_gradient) override;
};

#endif
