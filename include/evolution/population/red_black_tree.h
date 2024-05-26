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

        bool is_left_child_black_or_null()
        {
            return (this->left == nullptr || this->left->color == NodeColor::BLACK);
        }
        bool is_right_child_black_or_null()
        {
            return (this->right == nullptr || this->right->color == NodeColor::BLACK);
        }
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
        std::recursive_mutex lock;

    public:
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
            if (left->right != nullptr)
            {
                left->right->parent = rotation_point;
            }

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

            if (right->left != nullptr)
            {
                right->left->parent = rotation_point;
            }

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

        void fixup_delete_violations(IndividualNode<T> *replacing_node, IndividualNode<T> *replacing_node_parent, bool is_replacing_node_left_child)
        {
            IndividualNode<T> *replacing_node_sibling = nullptr;

            while ((replacing_node == nullptr) || (replacing_node != this->root && replacing_node->color == NodeColor::BLACK))
            {
                // get the replacing_node_sibling and replacing_node parent
                if (replacing_node == nullptr)
                {
                    replacing_node_sibling = is_replacing_node_left_child ? replacing_node_parent->right : replacing_node_parent->left;
                }
                else
                {
                    replacing_node_sibling = replacing_node->is_left_child() ? replacing_node->parent->right : replacing_node->parent->left;
                    replacing_node_parent = replacing_node->parent;
                }

                if ((replacing_node == nullptr && is_replacing_node_left_child) || ((replacing_node != nullptr) && (replacing_node->is_left_child())))
                {
                    if (replacing_node_sibling->color == NodeColor::RED)
                    {
                        replacing_node_sibling->color = NodeColor::BLACK;
                        replacing_node_parent->color = NodeColor::RED;
                        this->left_rotate(replacing_node_parent);
                        replacing_node_sibling = replacing_node_parent->right;
                    }
                    if (replacing_node_sibling->is_left_child_black_or_null() && replacing_node_sibling->is_right_child_black_or_null())
                    {
                        replacing_node_sibling->color = NodeColor::RED;
                        replacing_node = replacing_node_parent;
                    }
                    else
                    {
                        if (replacing_node_sibling->is_right_child_black_or_null())
                        {
                            if (replacing_node_sibling->left != nullptr)
                            {
                                replacing_node_sibling->left->color = NodeColor::BLACK;
                            }
                            replacing_node_sibling->color = NodeColor::RED;
                            this->right_rotate(replacing_node_sibling);
                            replacing_node_sibling = replacing_node_parent->right;
                        }
                        replacing_node_sibling->color = replacing_node_parent->color;
                        replacing_node_parent->color = NodeColor::BLACK;
                        replacing_node_sibling->right->color = NodeColor::BLACK;
                        this->left_rotate(replacing_node_parent);
                        replacing_node = this->root;
                    }
                }
                else
                {
                    if (replacing_node_sibling->color == NodeColor::RED)
                    {
                        replacing_node_sibling->color = NodeColor::BLACK;
                        replacing_node_parent->color = NodeColor::RED;
                        this->right_rotate(replacing_node_parent);
                        replacing_node_sibling = replacing_node_parent->left;
                    }
                    if (replacing_node_sibling->is_left_child_black_or_null() && replacing_node_sibling->is_right_child_black_or_null())
                    {
                        replacing_node_sibling->color = NodeColor::RED;
                        replacing_node = replacing_node_parent;
                    }
                    else
                    {
                        if (replacing_node_sibling->is_left_child_black_or_null())
                        {
                            if (replacing_node_sibling->right != nullptr)
                            {
                                replacing_node_sibling->right->color = NodeColor::BLACK;
                            }
                            replacing_node_sibling->color = NodeColor::RED;
                            this->left_rotate(replacing_node_sibling);
                            replacing_node_sibling = replacing_node_parent->left;
                        }
                        replacing_node_sibling->color = replacing_node_parent->color;
                        replacing_node_parent->color = NodeColor::BLACK;

                        if (replacing_node_sibling->left != nullptr)
                        {
                            replacing_node_sibling->left->color = NodeColor::BLACK;
                        }
                        this->right_rotate(replacing_node_parent);
                        replacing_node = this->root;
                    }
                }
            }
            replacing_node->color = NodeColor::BLACK;
        }

        IndividualNode<T> *root;
        uint32_t num_nodes;
        RedBlackTree() : root(nullptr), num_nodes(0) {}
        std::string bfsPrint()
        {
            if (this->root == nullptr)
                return "NULL TREE\n";

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
            std::lock_guard<std::recursive_mutex> lock(this->lock);
            this->root = binary_search_tree_insert(root, node);
            this->fixup_insert_violations(node);
            this->num_nodes++;
        }

        /// @brief Transplant subtree v into u position
        /// @param transplant_position
        /// @param subtree
        void subtreeTransplant(IndividualNode<T> *transplant_position, IndividualNode<T> *subtree)
        {
            if (this->root == transplant_position)
                this->root = subtree;
            else if (transplant_position->is_left_child())
                transplant_position->parent->left = subtree;
            else
                transplant_position->parent->right = subtree;

            if (subtree != nullptr)
                subtree->parent = transplant_position->parent;
        }

        /*
            Reference: https://www.programiz.com/dsa/deletion-from-a-red-black-tree
            Correspond symbol to the reference:
                - node_to_be_deleted: z
                - replacing_node: x
                - intermediate_node: y
        */
        void _remove(IndividualNode<T> *node_to_be_deleted)
        {
            assert(node_to_be_deleted != nullptr && "Invalid node to delete");
            if (node_to_be_deleted == this->root && this->num_nodes == 1)
            {
                this->root = nullptr;
            }
            else
            {
                IndividualNode<T> *intermediate_node = nullptr, *replacing_node = nullptr, *replacing_node_parent = nullptr;
                bool is_replacing_node_left_child;
                intermediate_node = node_to_be_deleted;
                NodeColor y_originalColor = intermediate_node->color;

                // if the node has only one or no children
                if (node_to_be_deleted->left == nullptr)
                {
                    replacing_node = node_to_be_deleted->right;
                    replacing_node_parent = node_to_be_deleted->parent;
                    is_replacing_node_left_child = node_to_be_deleted->is_left_child();
                    this->subtreeTransplant(node_to_be_deleted, replacing_node);
                }
                else if (node_to_be_deleted->right == nullptr)
                {
                    replacing_node = node_to_be_deleted->left;
                    replacing_node_parent = node_to_be_deleted->parent;
                    is_replacing_node_left_child = node_to_be_deleted->is_left_child();
                    this->subtreeTransplant(node_to_be_deleted, replacing_node);
                }

                // the node has two children
                else
                {
                    // find smallest node in the right subtree
                    intermediate_node = node_to_be_deleted->right;
                    while (intermediate_node->left != nullptr)
                        intermediate_node = intermediate_node->left;

                    y_originalColor = intermediate_node->color;
                    replacing_node = intermediate_node->right;
                    replacing_node_parent = intermediate_node;
                    is_replacing_node_left_child = false;

                    if (intermediate_node->parent != node_to_be_deleted)
                    {
                        is_replacing_node_left_child = intermediate_node->is_left_child();
                        replacing_node_parent = intermediate_node->parent;
                        this->subtreeTransplant(intermediate_node, replacing_node);

                        intermediate_node->right = node_to_be_deleted->right;
                        intermediate_node->right->parent = intermediate_node;
                    }
                    this->subtreeTransplant(node_to_be_deleted, intermediate_node);
                    intermediate_node->left = node_to_be_deleted->left;
                    intermediate_node->left->parent = intermediate_node;
                    intermediate_node->color = node_to_be_deleted->color;
                }

                if (y_originalColor == NodeColor::BLACK)
                    this->fixup_delete_violations(replacing_node, replacing_node_parent, is_replacing_node_left_child);
            }

            delete node_to_be_deleted;
            this->num_nodes--;
        }

        // Function to remove the smallest node
        void remove_smallest_node()
        {
            std::lock_guard<std::recursive_mutex> lock(this->lock);
            if (root == nullptr)
                return;

            auto smallest = this->get_smallest_node();

            if (smallest != nullptr)
            {
                this->_remove(smallest);
            }
        }

        // Function to get the smallest node
        IndividualNode<T> *get_smallest_node()
        {
            if (this->root == nullptr)
                return nullptr;

            IndividualNode<T> *node = this->root;

            while (node->left != nullptr)
            {
                node = node->left;
            }
            return node;
        }

        // Function to get the largest node
        IndividualNode<T> *get_largest_node()
        {
            std::lock_guard<std::recursive_mutex> lock(this->lock);
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
            std::lock_guard<std::recursive_mutex> lock(this->lock);
            if (this->root == nullptr)
                return nullptr;

            IndividualNode<T> *node = this->root;
            int direction;

            while (true)

            { // probability of choosing the left child, current node or the right child
                std::vector<float> direction_probs;

                if (node->left != nullptr)
                    direction_probs.push_back(1);
                else
                    direction_probs.push_back(0);

                direction_probs.push_back(1);

                if (node->right != nullptr)
                    direction_probs.push_back(5);
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
