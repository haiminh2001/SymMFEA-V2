
#include <map>
#include "utils/random_utils.h"
#include "components/primitive.h"
#include "components/functions/sum.h"
#include "components/functions/product.h"
#include "components/functions/tanh.h"
#include "components/functions/operand.h"
#include "components/functions/relu.h"

Node *createOperand(int index = -1, int arity = -1)
{
    return new Operand(index);
}

Node *createSum(int index = -1, int arity = -1)
{
    return new Sum(arity);
}

Node *createTanh(int index = -1, int arity = -1)
{
    return new Tanh();
}

Node *createRelu(int index = -1, int arity = -1)
{
    return new Relu();
}

Node *createProduct(int index = -1, int arity = -1)
{
    return new Product();
}

void Primitive::addNodeFactory(NodeFactory nf, int arity)
{
    this->functionList.emplace_back(nf, arity);
    this->possibleArities.push_back(arity);
}

void Primitive::removeDuplicatePossibleArites()
{
    std::sort(this->possibleArities.begin(), this->possibleArities.end());
    this->possibleArities.erase(std::unique(this->possibleArities.begin(), this->possibleArities.end()), this->possibleArities.end());
}

Primitive::Primitive()
{
    this->addNodeFactory(createOperand, 0);
    this->addNodeFactory(createSum, -1);
    this->addNodeFactory(createProduct, 2);
    this->addNodeFactory(createTanh, 1);
    this->addNodeFactory(createRelu, 1);
    this->removeDuplicatePossibleArites();
}

Primitive::Primitive(int max_index) : Primitive::Primitive()
{
    this->max_index = max_index;
}

NodeFactory random_select(std::vector<NodeFactory> candidates)
{

    auto randomIndex = Random::randint<uint64_t>(0, candidates.size() - 1);
    return candidates[randomIndex];
}

NodeFactory Primitive::getFunction(int expected_arity)
{
    std::vector<NodeFactory> candidates;
    for (auto function : this->functionList)
    {
        int arity = std::get<1>(function);
        if (arity == expected_arity)
        {
            candidates.emplace_back(std::get<0>(function));
        }
    }
    return random_select(candidates);
}

Node *Primitive::sampleNode(int arity_min, int arity_max)
{
    auto n_arity = Random::randint<int>(0, 1);

    int actual_arity;

    if (n_arity == 1)
    {
        actual_arity = Random::randint<int>(arity_min, arity_max);
    }
    else
    {
        actual_arity = Random::randint<int>(arity_min, std::min(2, arity_max));
    }

    int arity;
    if (actual_arity < 2 && actual_arity > -1)
        arity = actual_arity;
    else if (actual_arity == 2)
    {
        auto dynamic = Random::randint<int>(0, 1);
        if (dynamic > 0)
            arity = -1;
        else
            arity = actual_arity;
    }
    else
        arity = -1;

    auto nf = this->getFunction(arity);

    int node_index = -1;

    if (arity == 0)
    {
        node_index = Random::randint<int>(0, this->max_index);
    }

    return nf(node_index, actual_arity);
}