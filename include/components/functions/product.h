
#include "node.h"

class Product : public Node{
    public:
        ArrayXXf eval(std::vector <ArrayXXf> X) override;
        Product(int index) : Node(2, index) {}
};