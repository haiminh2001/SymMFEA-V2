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

    template <typename T>
    class IndividualNode
    {
    private:
    public:
        T data;
        float value;
        IndividualNode *parent;
        IndividualNode *left;
        IndividualNode *right;
        NodeColor color;

        IndividualNode() : parent(nullptr), left(nullptr), right(nullptr), color(NodeColor::RED) {}
        IndividualNode(T individual);
    };

    template <typename T>
    IndividualNode<T> *successor(IndividualNode<T> *node);

    // function to perform BST insertion of a Node
    template <typename T>
    IndividualNode<T> *binary_search_tree_insert(IndividualNode<T> *root, IndividualNode<T> *temp);

    template <typename T>
    void swap_position_on_tree(IndividualNode<T> *a, IndividualNode<T> *b);

    template <typename T>
    void binary_search_tree_delete(IndividualNode<T> *node);

    template <typename T>
    class RedBlackTree
    {
    private:
        std::mutex lock;
        IndividualNode<T> *root;

        // Function performing right rotation
        // of the passed Node
        void right_rotate(IndividualNode<T> *temp);

        // Function performing left rotation
        // of the passed Node
        void left_rotate(IndividualNode<T> *temp);

        // This function fixes violations
        // caused by BST insertion
        void fixup(IndividualNode<T> *pt);

    public:
        uint32_t num_nodes;
        RedBlackTree() : root(nullptr), num_nodes(0) {}
        std::string bfsPrint();

        // Function to insert a node into the Red-Black Tree
        void insert(IndividualNode<T> *node);

        // Function to remove the smallest node
        void remove_smallest_node();

        // Function to get the largest node
        IndividualNode<T> *get_largest_node();

        IndividualNode<T> *get_random_node();
    };

}

#endif // SYMMFEA_RED_BLACK_TREE_H
