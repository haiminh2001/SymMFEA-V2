#ifndef PRODUCT_H
#define PRODUCT_H

#include "node.h"

class Product : public Node{
public:
    explicit Product();

    ArrayXf eval(std::stack <ArrayXf>& X) override;

};

#endif
