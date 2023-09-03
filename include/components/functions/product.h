#ifndef PRODUCT_H
#define PRODUCT_H

#include "node.h"

class Product : public Node{
public:
    ArrayXf eval(std::stack <ArrayXf>& X) override;
    explicit Product(int index) : Node(2, index){};
};

#endif
