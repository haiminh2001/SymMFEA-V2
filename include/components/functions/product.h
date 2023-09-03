#ifndef PRODUCT_H
#define PRODUCT_H

#include "node.h"

class Product : public Node{
public:
    ArrayXXf eval(std::vector <ArrayXXf> X) override;
    explicit Product(int index) : Node(2, index){};
};

#endif
