#ifndef SYMMFEA_AQ_H
#define SYMMFEA_AQ_H

#include "node.h"

class Aq : public Node
{
private:
    ArrayXf _forward(std::stack<ArrayXf> &X, bool record_gradient) override;

public:
    explicit Aq();
    Node *clone() override;
};
#endif // SYMMFEA_AQ_H
