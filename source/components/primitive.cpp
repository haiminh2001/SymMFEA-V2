#include "primitive.h"
#include "operand.h"
#include "sum.h"
#include "product.h"
#include <map>
#include <random>

Node* createOperand(int index, int arity = -1){
    return new Operand(index);
}

Node* createSum(int arity, int index=-1){
    return new Sum(arity);
}

Node* createProduct(int index = -1, int arity = -1){
    return new Product();
}



Primitive::Primitive() {
    this->functionList.emplace_back(createOperand, 0);
    this->functionList.emplace_back(createSum, -1);
    this->functionList.emplace_back(createProduct, 2);
}


NodeFactory random_select(std::vector <NodeFactory> candidates){
    std::random_device rd;
    std::mt19937 rng(rd());

    // Randomly select an element
    std::uniform_int_distribution<unsigned long> dist(0, candidates.size() - 1);
    auto randomIndex = dist(rng);
    return candidates[randomIndex];
}

NodeFactory Primitive::getFunction(int expected_arity) {
    std::vector< NodeFactory > candidates;
    for (auto function : this->functionList){
        int arity = std::get<1>(function);
        if (arity == expected_arity){
            candidates.emplace_back(std::get<0>(function));
        }
    }
    return  random_select(candidates);
}