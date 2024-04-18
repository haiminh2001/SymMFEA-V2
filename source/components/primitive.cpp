
#include <map>
#include "utils/random_utils.h"
#include "components/primitive.h"
#include "components/functions/sum.h"
#include "components/functions/product.h"
#include "components/functions/tanh.h"
#include "components/functions/operand.h"
#include "components/functions/relu.h"

Node *createOperand(int index, int arity)
{
    return new Operand(index);
}

Node *createSum(int index, int arity)
{
    return new Sum(arity);
}

Node *createTanh(int index, int arity)
{
    return new Tanh();
}

Node *createRelu(int index, int arity)
{
    return new Relu();
}

Node *createProduct(int index, int arity)
{
    return new Product();
}

void Primitive::addNodeFactory(NodeFactory nf, int arity)
{
    this->functionList.emplace_back(nf, arity);
    this->useable_indices.push_back(arity);
}

void Primitive::removeDuplicatePossibleNumArites()
{
    std::sort(this->useable_indices.begin(), this->useable_indices.end());
    this->useable_indices.erase(std::unique(this->useable_indices.begin(), this->useable_indices.end()), this->useable_indices.end());
}

Primitive::Primitive()
{
    this->addNodeFactory(createOperand, 0);
    this->addNodeFactory(createSum, -1);
    this->addNodeFactory(createProduct, 2);
    this->addNodeFactory(createTanh, 1);
    this->addNodeFactory(createRelu, 1);
    this->removeDuplicatePossibleNumArites();
}

Primitive::Primitive(std::vector<int> useable_indices) : Primitive::Primitive()
{
    this->useable_indices = useable_indices;
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

    // arity can be -1, which indicates that the node can have a dynamic number of arities
    // actual_arity is the actual number of arities that the node will have
    int actual_arity, arity;

    actual_arity = Random::randint<int>(arity_min, arity_max);

    if (actual_arity < 2)
    {
        arity = actual_arity;
    }

    else if (actual_arity == 2)
    {
        auto dynamic = Random::randint<int>(0, 1);

        // if dynamic
        if (dynamic == 1)
            arity = -1;
        else
            arity = 2;
    }
    else
    {
        // actual_arity > 2 means dynamic
        arity = -1;
    }

    auto nf = this->getFunction(arity);

    // default index is -1 indicates that the node is not an operand
    int node_index = -1;

    // if the node is an operand, then the index is randomly selected from the list of useable indices
    if (actual_arity == 0)
    {
        node_index = this->useable_indices[Random::randint<int>(0, this->useable_indices.size() - 1)];
    }

    return nf(node_index, actual_arity);
}