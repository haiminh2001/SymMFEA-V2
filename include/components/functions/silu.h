#ifndef SYMMFEA_SILU_H
#define SYMMFEA_SILU_H

#include "node.h"

class Silu : public Node
{
private:
    ArrayXf _forward(std::stack<ArrayXf> &X, bool record_gradient) override;

public:
    explicit Silu();
    Node *clone() override;
};
#endif // SYMMFEA_SILU_H
