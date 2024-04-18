#include "components/tree/tree.h"
#include "central_units/individual_infos.h"
#include <utility>
#include <vector>
#include <stack>
#include <graphviz/gvc.h>
#include <fstream>
#include <tuple>

/// @brief
/// @param X 2d array of shape (n_samples, n_features)
/// @return 1d array of shape (n_samples, )
ArrayXf Tree::forward(const ArrayXXf &X, bool record_gradient)
{
    auto length = this->nodes.size();
    std::stack<ArrayXf> Stack;

    for (auto node : this->nodes)
    {

        ArrayXf val;

        if (node->is_leaf())
        {
            val = node->forward<ArrayXXf>(X, record_gradient);
        }
        else
        {
            val = node->forward<std::stack<ArrayXf> &>(Stack, record_gradient);
        }

        Stack.push(val);
    }

    // the stack should have only one element which is the final result
    assert(Stack.size() == 1);
    return Stack.top();
}

int Tree::length()
{
    return this->nodes[this->nodes.size() - 1]->length + 1;
}

int Tree::depth()
{
    return this->nodes[this->nodes.size() - 1]->depth;
}

/// @brief update the metadata of the nodes
/// @param central_id the id of the trees in the IndividualInfos
void Tree::updateNodeMetadata(int64_t central_id)
{
    auto length = this->nodes.size();
    for (int i = 0; i < length; ++i)
    {
        auto node = this->nodes[i];
        node->depth = 1;
        node->length = node->arity;
        node->id = i;
        node->central_id = central_id;
        if (node->is_leaf())
        {

            continue;
        }

        int j = i - 1;
        int num_children = node->arity;
        for (int k = 0; k < num_children; ++k)
        {
            auto child = this->nodes[j];
            node->length += child->length;
            node->depth = std::max(node->depth, child->depth);
            j -= child->length + 1;
        }

        node->depth += 1;
    }

    assert(this->length() == this->nodes.size());
}

Tree::Tree(std::vector<Node *> nodes, int64_t central_id) : central_id(central_id)
{
    this->nodes = std::move(nodes);
    this->updateNodeMetadata(central_id);
}

void printSubTree(uint64_t x, uint64_t y, std::vector<Node *> nodes,
                  uint64_t index, std::ofstream &outputFile)
{
    // x, y is the position of the node

    auto node = nodes[index];

    outputFile << "\tnode" << index << " [label=\"" << node->symbol.c_str() << "\"];" << std::endl;

    uint64_t cur_index = index - 1;

    for (int i = 0; i < node->arity; ++i)
    {
        uint64_t new_x = x - y / (index + 1);
        uint64_t new_y = y + 50;
        outputFile << "\tnode" << index << " -> node" << cur_index << ";" << std::endl;
        printSubTree(new_x, new_y, nodes, cur_index, outputFile);

        cur_index -= nodes[cur_index]->length + 1;
    }
}

void Tree::visualize()
{
    std::ofstream outputFile("/tmp/tree.dot");
    outputFile << "digraph Tree {" << std::endl;
    printSubTree(300, 100, this->nodes, this->nodes.size() - 1, outputFile);
    outputFile << "}" << std::endl;
    outputFile.close();
    std::system("dot -Tpng /tmp/tree.dot -o tree.png");
};

/// @brief
/// @param split_point the index of the node to split the tree
/// @return a tuple of 3 elements, the first element is the branch, the second element is the first part of the root, the third element is the second part of the root
std::tuple<std::vector<Node *>, std::tuple<std::vector<Node *>, std::vector<Node *>>> Tree::split_tree(int split_point)
{
    std::vector<Node *> branch(this->nodes.begin() + split_point - this->nodes[split_point]->length, this->nodes.begin() + split_point + 1);
    std::vector<Node *> root1(this->nodes.begin(), this->nodes.begin() + split_point - this->nodes[split_point]->length);
    std::vector<Node *> root2(this->nodes.begin() + split_point + 1, this->nodes.end());
    return std::make_tuple(branch, std::make_tuple(root1, root2));
}

std::ostream &operator<<(std::ostream &os, const Tree &tree)
{
    os << "Tree information:" << std::endl;
    for (auto node : tree.nodes)
    {
        os << "  " << node->id << ": ";
        os << *node;
    }

    return os;
}

void Tree::setWeight(std::vector<float> weight)
{
    auto row = IndividualInfos::weight.row(this->central_id);
    for (int i = 0; i < weight.size(); ++i)
    {
        row(i) = weight[i];
    }
}