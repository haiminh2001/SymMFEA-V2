#ifndef SYMMFEA_RED_BLACK_TREE_H
#define SYMMFEA_RED_BLACK_TREE_H
#include "evolution/population/individual.h"
#include "utils/random_utils.h"

#include <queue>
#include <mutex>
#include <memory>
#include <iostream>

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

        // Default color of a new node is red
        IndividualNode() : parent(nullptr), left(nullptr), right(nullptr), color(NodeColor::RED) {}
        IndividualNode(T data) : IndividualNode()
        {
            this->data = data;
        }
    };

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
        else
        {
            root->right = binary_search_tree_insert(root->right, temp);
            root->right->parent = root;
        }

        // Return the (unchanged) Node pointer
        return root;
    }

    template <typename T>
    class RedBlackTree
    {
    private:
        std::mutex lock;

    public:
        void swap_position_on_tree(IndividualNode<T> *a, IndividualNode<T> *b)
        {
            // swap root if one of the nodes is root
            IndividualNode<T> *temp;
            if (this->root == a)
            {
                this->root = b;
            }
            else if (this->root == b)
            {
                this->root = a;
            }

            // swap parent
            if (b->parent)
            {
                if (b->is_left_child())
                    b->parent->left = a;
                else
                    b->parent->right = a;
            }
            if (a->parent)
            {
                if (a->is_left_child())
                    a->parent->left = b;
                else
                    a->parent->right = b;
            }
            temp = a->parent;
            a->parent = b->parent;
            b->parent = temp;

            // swap left child
            temp = a->left;
            a->left = b->left;
            if (a->left)
                a->left->parent = a;

            b->left = temp;
            if (b->left)
                b->left->parent = b;

            // swap right child
            temp = a->right;
            a->right = b->right;
            if (a->right)
                a->right->parent = a;

            b->right = temp;
            if (b->right)
                b->right->parent = b;

            // auto temp_color = a->color;
            // a->color = b->color;
            // b->color = temp_color;
        }

        // Function performing right rotation of the subtree with the root node is passed
        void right_rotate(IndividualNode<T> *rotation_point)
        {
            IndividualNode<T> *left = rotation_point->left;

            assert(left != nullptr && "Invalid right rotation, no left child!!");

            // attach the left node to the parent of the current node
            left->parent = rotation_point->parent;
            if (rotation_point == this->root)
            {
                root = left;
            }
            else
            {
                if (rotation_point->is_left_child())
                {
                    rotation_point->parent->left = left;
                }
                else
                {
                    rotation_point->parent->right = left;
                }
            }
            // attach the right of the left child to the left of the temp node
            rotation_point->left = left->right;

            // attach the temp node as the right child of the left node
            left->right = rotation_point;
            rotation_point->parent = left;
        }

        // Function performing right rotation of the subtree with the root node is passed
        void left_rotate(IndividualNode<T> *rotation_point)
        {
            IndividualNode<T> *right = rotation_point->right;

            assert(right != nullptr && "Invalid left rotation, no right child!!");

            // attach the right node to the parent of the current node
            right->parent = rotation_point->parent;
            if (rotation_point == this->root)
            {
                root = right;
            }
            else
            {
                if (rotation_point->is_left_child())
                {
                    rotation_point->parent->left = right;
                }
                else
                {
                    rotation_point->parent->right = right;
                }
            }
            // attach the left of the right child to the right of the temp node
            rotation_point->right = right->left;

            // attach the temp node as the left child of the right node
            right->left = rotation_point;
            rotation_point->parent = right;
        }

        // This function fixes violations
        // caused by BST insertion
        // reference: https://www.programiz.com/dsa/insertion-in-a-red-black-tree
        void fixup_insert_violations(IndividualNode<T> *new_node)
        {
            IndividualNode<T> *parent = nullptr;
            IndividualNode<T> *grandparent = nullptr;
            IndividualNode<T> *uncle = nullptr;

            while ((new_node != this->root) && (new_node->parent->color == NodeColor::RED))
            {
                parent = new_node->parent;
                grandparent = new_node->parent->parent;
                uncle = (parent == grandparent->left) ? grandparent->right : grandparent->left;

                /*  Case : A
                Parent of new_node is left child
                of Grand-parent of new_node */
                if (parent->is_left_child())
                {
                    /* Case-I*/
                    if (uncle != nullptr && uncle->color == NodeColor::RED)
                    {
                        grandparent->color = NodeColor::RED;
                        parent->color = NodeColor::BLACK;
                        uncle->color = NodeColor::BLACK;
                        new_node = grandparent;
                    }

                    else
                    {
                        /* Case-II*/
                        if (new_node->is_right_child())
                        {
                            new_node = parent;
                            this->left_rotate(new_node);
                        }

                        /* Case-III */
                        else
                        {
                            parent->color = NodeColor::BLACK;
                            grandparent->color = NodeColor::RED;
                            this->right_rotate(grandparent);
                        }
                    }
                }

                /* Case : B
                Parent of new_node is right
                child of Grand-parent of
                new_node */
                else
                {
                    /* Case-I*/
                    if (uncle != nullptr && uncle->color == NodeColor::RED)
                    {
                        grandparent->color = NodeColor::RED;
                        parent->color = NodeColor::BLACK;
                        uncle->color = NodeColor::BLACK;
                        new_node = grandparent;
                    }
                    else
                    {
                        /* Case-II*/
                        if (new_node->is_left_child())
                        {
                            new_node = parent;
                            this->right_rotate(new_node);
                        }

                        /* Case-III */
                        else
                        {
                            parent->color = NodeColor::BLACK;
                            grandparent->color = NodeColor::RED;
                            this->left_rotate(grandparent);
                        }
                    }
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
            this->fixup_insert_violations(node);
            this->num_nodes++;
        }

        void fixup_delete_violation(IndividualNode<T> *node, IndividualNode < T >> *parent)
        {
            if (node == this->root)
            {
                this->root = nullptr;
                return;
            }
            // else if ((node->color == NodeColor::BLACK) 
            //          && (node->parent->color == NodeColor::BLACK)
            //          && ((node->right != nullptr) && (node->right->color == NodeColor::BLACK))
            //          && ((node->parent->right->left) == nullptr || (node->parent->right->right == nullptr))
            //          ){
            //     /*  
            //     In this case the black length of the subtree with the root is the parent is 3.
            //     But the sibling of the node is missing a children 
            //     so the number of nodes in the subtree with the root is the parent is 4, which is not possible
            //     to maintain the black length of the subtree 3 with the local manipulations, which requires at least 5 nodes.
            //     So instead of trying to fix the violation using global manipulations, just back off deletion.
            //     */
            //    return;
            // }
            else
            {
                parent->left = node->right;
            }

            if (node->color == NodeColor::BLACK)
            {
                // if the node is black then there must be a sibling with the same color
                assert(parent->right != nullptr && "Invalid deletion, no sibling found!!");
                auto sibling = parent->right;

                assert(sibling->color == NodeColor::BLACK && "The sibiling should be black");

                /* The mission is now to increase the number of black nodes of the local subtree
                   with the root is the parent left child to increase by one
                */

                // Case 1: The node had a right child, which now will be the left child of the parent
                if (parent->left != nullptr)
                {
                    // Case 1.1: The left child is red, just recolor it to black
                    if (parent->left->color == NodeColor::RED){
                        parent->left->color = NodeColor::BLACK;
                    }
                    // Case 1.2: The left child is already black, then the sibling has a least one black child
                    else{
                        /* In this case, initially, the black length of the parent was 3 if the parent was black
                           and 2 if the parent was red.
                        */

                        auto sibling = parent->right;

                        // Case 1.2.1: The parent is black
                        if (parent->color == NodeColor::BLACK){
                            // The sibling must have 2 black children 
                            assert((sibling->left != nullptr ) && (sibling->right != nullptr));

                            this->left_rotate(parent);
                            this->left_rotate(parent);
                            this->left_rotate(sibling->left);
                        }
                        // Case 1.2.2: The parent is red
                        else{
                            // Case 1.2.2-a) The sibling has 2 black children
                            if ((sibling->left != nullptr ) && (sibling->right != nullptr)){
                                this->left_rotate(parent);
                            }
                            // Case 1.2.2-b) The sibling has a black left children
                            else
                        }
                            
                    }
                }
                
            }
        }

        // Function to remove the smallest node
        void remove_smallest_node()
        {
            std::lock_guard<std::mutex> lock(this->lock);
            if (root == nullptr)
                return;

            IndividualNode<T> *node = root;
            IndividualNode<T> *parent;
            while (node->left != nullptr)
            {
                parent = node;
                node = node->left;
            }

            // fix up violation and detech the node from the tree
            this->fixup_delete_violation(node, parent);

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
