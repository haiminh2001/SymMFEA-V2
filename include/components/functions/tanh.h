#ifndef SYMMFEA_TANH_H
#define SYMMFEA_TANH_H

#include "node.h"

class Tanh : public Node
{
private:
    ArrayXf _forward(std::stack<ArrayXf> &X, bool record_gradient) override;

public:
    explicit Tanh();
    Node *clone() override;
};
#endif // SYMMFEA_TANH_H
