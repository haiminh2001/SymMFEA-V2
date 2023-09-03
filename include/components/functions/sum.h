#include "node.h"

class Sum : public Node{
    public:
        MatrixXf eval(std::vector <MatrixXf> X) override;
        Sum(int arity, int index) : Node(arity, index) {

        }
};