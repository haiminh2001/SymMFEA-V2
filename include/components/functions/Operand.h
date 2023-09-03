#ifndef SYMMFEA_OPERAND_H
#define SYMMFEA_OPERAND_H

#include "node.h"

class Operand : public Node{
public:
    explicit Operand(int index);

private:
    ArrayXf eval(std::stack <ArrayXf>& X) override;
};

#endif
