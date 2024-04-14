#ifndef SYMMFEA_RELU_H
#define SYMMFEA_RELU_H

#include "node.h"

class Relu : public Node
{
private:
    ArrayXf _forward(std::stack<ArrayXf> &X) override;

public:
    explicit Relu();
    Node *clone() override;
};
#endif // SYMMFEA_RELU_H
