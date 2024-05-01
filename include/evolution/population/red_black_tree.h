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

        bool is_left_child()
        {
            if (this->parent == nullptr)
                return false;

            return this->parent->left == this;
        }
        bool is_right_child()
        {
            if (this->parent == nullptr)
                return false;

            return this->parent->right == this;
        }

        std::string color_string()
        {
            return this->color == NodeColor::RED ? "RED" : "BLACK";
        }

        IndividualNode() : parent(nullptr), left(nullptr), right(nullptr), color(NodeColor::RED) {}
        IndividualNode(T data) : IndividualNode()
        {
            this->data = data;
        }
    };

    template <typename T>
    IndividualNode<T> *successor(IndividualNode<T> *node)
    {
        if (node->right != nullptr)
        {
            // If the node has a right child, find the leftmost node in the right subtree
            IndividualNode<T> *current = node->right;
            while (current->left != nullptr)
            {
                current = current->left;
            }
            return current;
        }
        else
        {
            // If the node does not have a right child, find the first ancestor that is a left child
            IndividualNode<T> *parent = node->parent;
            while (parent != nullptr && node == parent->right)
            {
                node = parent;
                parent = parent->parent;
            }
            return parent;
        }
    }

    // function to perform BST insertion of a Node
    template <typename T>
    IndividualNode<T> *binary_search_tree_insert(IndividualNode<T> *root, IndividualNode<T> *temp)
    {
        // If the tree is empty,
        // return a new Node
        if (!root)
            return temp;

        // Otherwise recur down the tree
        if (temp->value < root->value)
        {
            root->left = binary_search_tree_insert(root->left, temp);
            root->left->parent = root;
        }
        else if (temp->value > root->value)
        {
            root->right = binary_search_tree_insert(root->right, temp);
            root->right->parent = root;
        }

        // Return the (unchanged) Node pointer
        return root;
    }

    template <typename T>
    void swap_position_on_tree(IndividualNode<T> *a, IndividualNode<T> *b)
    {

        if (b->parent)
        {
            if (b->parent->left == b)
                b->parent->left = a;
            else
                b->parent->right = a;
        }
        if (a->parent)
        {
            if (a->parent->left == a)
                a->parent->left = b;
            else
                a->parent->right = b;
        }
        IndividualNode<T> *temp = a->parent;
        a->parent = b->parent;
        b->parent = temp;

        temp = a->left;
        a->left = b->left;
        if (a->left)
            a->left->parent = a;

        b->left = temp;
        if (b->left)
            b->left->parent = b;

        temp = a->right;
        a->right = b->right;
        if (a->right)
            a->right->parent = a;

        b->right = temp;
        if (b->right)
            b->right->parent = b;
    }

    template <typename T>
    void binary_search_tree_delete(IndividualNode<T> *node)
    {
        if (node == nullptr)
            return;

        if ((!node->left) && (!node->right))
        {
            if (node->parent)
            {
                if (node->parent->left == node)
                    node->parent->left = nullptr;
                else
                    node->parent->right = nullptr;
            }
            delete node;
        }
        else if ((!node->left) || (!node->right))
        {
            IndividualNode<T> *child = node->left ? node->left : node->right;
            if (node->parent)
            {
                if (node->parent->left == node)
                    node->parent->left = child;
                else
                    node->parent->right = child;
            }
            delete node;
        }

        else
        {
            IndividualNode<T> *successor_node = successor(node);

            swap_position_on_tree(node, successor_node);

            binary_search_tree_delete(node);
        }
    }

    template <typename T>
    class RedBlackTree
    {
    private:
        std::mutex lock;

    public:
        // Function performing right rotation of the subtree with the root node is passed
        void right_rotate(IndividualNode<T> *temp)
        {
            IndividualNode<T> *left = temp->left;
            temp->left = left->right;
            if (temp->left)
                temp->left->parent = temp;
            left->parent = temp->parent;
            if (!temp->parent)
                root = left;
            else if (temp == temp->parent->left)
                temp->parent->left = left;
            else
                temp->parent->right = left;
            left->right = temp;
            temp->parent = left;
        }

        // Function performing right rotation of the subtree with the root node is passed
        void left_rotate(IndividualNode<T> *temp)
        {
            IndividualNode<T> *right = temp->right;

            assert(right != nullptr && "Invalid left rotation, no right child!!");

            // attach the right node to the parent of the current node
            right->parent = temp->parent;
            if (temp->parent == nullptr)
            {
                root = right;
            }
            else
            {
                if (temp->is_left_child())
                {
                    temp->parent->left = right;
                }
                else
                {
                    temp->parent->right = right;
                }
            }
            // attach the left of the right child to the right of the temp node
            temp->right = right->left;
            
            // attach the temp node as the left child of the right node
            right->left = temp;
            temp->parent = right;

            
        }

        // This function fixes violations
        // caused by BST insertion
        void fixup(IndividualNode<T> *pt)
        {
            IndividualNode<T> *parent_pt = nullptr;
            IndividualNode<T> *grand_parent_pt = nullptr;
            IndividualNode<T> *uncle_pt = nullptr;

            while ((pt != this->root) && (pt->parent->color == NodeColor::RED))
            {
                parent_pt = pt->parent;
                grand_parent_pt = pt->parent->parent;
                uncle_pt = (parent_pt == grand_parent_pt->left) ? grand_parent_pt->right : grand_parent_pt->left;
                // not implement yet
                break;
                /*  Case : A
                Parent of pt is left child
                of Grand-parent of pt */
                if (parent_pt == grand_parent_pt->left)
                {
                }

                /* Case : B
                     Parent of pt is right
                     child of Grand-parent of
                   pt */
                else
                {
                }
            }
            this->root->color = NodeColor::BLACK;
        }

        IndividualNode<T> *root;
        uint32_t num_nodes;
        RedBlackTree() : root(nullptr), num_nodes(0) {}
        std::string bfsPrint()
        {
            std::string result = "";
            std::queue<IndividualNode<T> *> queue;

            queue.push(root);

            while (!queue.empty())
            {

                auto current_node = queue.front();
                queue.pop();
                if (current_node->left || current_node->right)
                {

                    result += std::to_string(current_node->value) + "(" + current_node->color_string() + ") " + ": ";
                    if (current_node->left)
                    {
                        queue.push(current_node->left);
                        result += std::to_string(current_node->left->value) + "(" + current_node->left->color_string() + ") " + " ";
                    }
                    if (current_node->right)
                    {
                        queue.push(current_node->right);

                        result += std::to_string(current_node->right->value) + "(" + current_node->right->color_string() + ") " + " ";
                    }
                    result += '\n';
                }
            }
            return result;
        }

        // Function to insert a node into the Red-Black Tree
        void insert(IndividualNode<T> *node)
        {
            std::lock_guard<std::mutex> lock(this->lock);
            this->root = binary_search_tree_insert(root, node);
            this->fixup(node);
            this->num_nodes++;
        }

        // Function to remove the smallest node
        void remove_smallest_node()
        {
            std::lock_guard<std::mutex> lock(this->lock);
            if (root == nullptr)
                return;

            IndividualNode<T> *node = root;
            IndividualNode<T> *p;
            while (node->left != nullptr)
            {
                p = node;
                node = node->left;
            }
            p->left = node->right;
            delete node;
            this->num_nodes--;
        }

        // Function to get the largest node
        IndividualNode<T> *get_largest_node()
        {
            if (root == nullptr)
                return nullptr;

            IndividualNode<T> *node = root;

            while (node->right != nullptr)
            {
                node = node->right;
            }
            return node;
        }

        // NOTE: may implement a different logic to handle different height of the tree
        IndividualNode<T> *get_random_node()
        {
            if (root == nullptr)
                return nullptr;

            IndividualNode<T> *node = root;
            int direction;

            while (true)

            { // probability of choosing the left child, current node or the right child
                std::vector<float> direction_probs;

                if (node->left)
                    direction_probs.push_back(1);
                else
                    direction_probs.push_back(0);

                direction_probs.push_back(4);

                if (node->right)
                    direction_probs.push_back(10);
                else
                    direction_probs.push_back(0);

                direction = Random::random_choice<int>(direction_probs);

                if (direction == 2)
                    node = node->right;
                else if (direction == 1)
                    break;
                else
                    node = node->left;
            }

            return node;
        }
    };

}

#endif // SYMMFEA_RED_BLACK_TREE_H
