#ifndef SYMMFEA_RED_BLACK_TREE_H
#define SYMMFEA_RED_BLACK_TREE_H
#include "evolution/population/individual.h"
#include "utils/random_utils.h"

#include <iostream>
#include <queue>
#include <mutex>
#include <memory>

namespace RedBlackTree
{
    enum class NodeColor
    {
        RED,
        BLACK
    };

    class IndividualNode
    {
    private:
    public:
        std::shared_ptr<Individual> individual;
        float value;
        IndividualNode *parent;
        IndividualNode *left;
        IndividualNode *right;
        NodeColor color;

        IndividualNode() : parent(nullptr), left(nullptr), right(nullptr), color(NodeColor::RED) {}
        IndividualNode(std::shared_ptr<Individual> individual);
    };

    IndividualNode *successor(IndividualNode *node);

    // function to perform BST insertion of a Node
    IndividualNode *binary_search_tree_insert(IndividualNode *root, IndividualNode *temp);

    void swap_position_on_tree(IndividualNode *a, IndividualNode *b);

    void binary_search_tree_delete(IndividualNode *node);

    class RedBlackTree
    {
    private:
        std::mutex lock;
        IndividualNode *root;

        // Function performing right rotation
        // of the passed Node
        void right_rotate(IndividualNode *temp);

        // Function performing left rotation
        // of the passed Node
        void left_rotate(IndividualNode *temp);

        // This function fixes violations
        // caused by BST insertion
        void fixup(IndividualNode *pt);

    public:
        uint32_t num_nodes;
        RedBlackTree() : root(nullptr), num_nodes(0) {}
        std::string bfsPrint();

        // Function to insert a node into the Red-Black Tree
        void insert(IndividualNode *node);

        // Function to remove the smallest node
        void remove_smallest_node();

        // Function to get the largest node
        IndividualNode *get_largest_node();

        IndividualNode *get_random_node();
    };

}

#endif // SYMMFEA_RED_BLACK_TREE_H
