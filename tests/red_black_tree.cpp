#include "gtest/gtest.h"
#include "evolution/population/red_black_tree.h"

#include <iostream>
#include <stack>
#include <tuple>

#define create_node(val)                                \
    tmp_node = new RedBlackTree::IndividualNode<int>(); \
    tmp_node->value = val;
class RedBlackTreeTest : public ::testing::Test
{
protected:
    RedBlackTree::RedBlackTree<int> *tree;
    RedBlackTree::IndividualNode<int> *tmp_node;

    void SetUp() override
    {
        tree = new RedBlackTree::RedBlackTree<int>();
    }

    void TearDown() override
    {
        delete tree;
    }

    void checkRedNodeNotHaveRedChild(RedBlackTree::IndividualNode<int> *node)
    {
        if (node == nullptr)
        {
            return;
        }
        checkRedNodeNotHaveRedChild(node->left);

        // check
        if (node->color == RedBlackTree::NodeColor::RED)
        {
            ASSERT_TRUE(node->left == nullptr || node->left->color == RedBlackTree::NodeColor::BLACK);
            ASSERT_TRUE(node->right == nullptr || node->right->color == RedBlackTree::NodeColor::BLACK);
        }

        checkRedNodeNotHaveRedChild(node->right);
    }

    void checkParent(RedBlackTree::IndividualNode<int> *node)
    {
        if (node == nullptr)
        {
            return;
        }

        checkParent(node->left);

        // check
        if (node == this->tree->root)
        {
            ASSERT_TRUE(node->parent == nullptr);
        }
        else
        {
            ASSERT_TRUE(node->parent != nullptr);
        }

        checkParent(node->right);
    }
    void checkBlackPathLength()
    {
        int any_leaf_black_path_length = -1;
        std::stack<std::tuple<RedBlackTree::IndividualNode<int> *, int>> Stack;

        Stack.push(std::make_tuple(tree->root, 1));

        while (!Stack.empty())
        {
            auto [node, black_path_length] = Stack.top();
            Stack.pop();

            if (node == nullptr)
            {
                // leaf node
                if (any_leaf_black_path_length == -1)
                    any_leaf_black_path_length = black_path_length;
                else
                    ASSERT_EQ(black_path_length, any_leaf_black_path_length);
            }

            else
            {
                int current_black_path_length = black_path_length + (node->color == RedBlackTree::NodeColor::BLACK ? 1 : 0);
                Stack.push(std::make_tuple(node->left, current_black_path_length));
                Stack.push(std::make_tuple(node->right, current_black_path_length));
            }
        }
    }
    void checkIsBinarySeachTree(RedBlackTree::IndividualNode<int> *node)
    {
        if (node == nullptr)
        {
            return;
        }
        checkIsBinarySeachTree(node->left);

        // since the value is float, equal is not deterministic
        if (node->left != nullptr)
            ASSERT_GE(node->value, node->left->value);
        if (node->right != nullptr)
            ASSERT_GE(node->right->value, node->value);

        checkIsBinarySeachTree(node->right);
    }
};

TEST_F(RedBlackTreeTest, RotateLeft)
{

    /*
        * Test rotate left
        *     10
        *    /  \
        *   5   15
        *  / \
        * 3   7
        *    / \
        *   6   8
        * After rotate left
        *       10
        *      /  \
        *     7   15
        *    / \
        *   5   8
        *  / \
        * 3   6

    */

    create_node(10);
    tree->root = tmp_node;
    RedBlackTree::IndividualNode<int> *rotate_point;
    RedBlackTree::IndividualNode<int> *right_child_of_rotate_point;
    RedBlackTree::IndividualNode<int> *left_child_of_right_child_of_rotate_point;

    create_node(5);
    tree->root->left = tmp_node;
    tmp_node->parent = tree->root;
    rotate_point = tmp_node;

    create_node(15);
    tree->root->right = tmp_node;
    tmp_node->parent = tree->root;

    create_node(3);
    tree->root->left->left = tmp_node;
    tmp_node->parent = tree->root->left;

    create_node(7);
    tree->root->left->right = tmp_node;
    tmp_node->parent = tree->root->left;
    right_child_of_rotate_point = tmp_node;

    create_node(6);
    tree->root->left->right->left = tmp_node;
    tmp_node->parent = tree->root->left->right;
    left_child_of_right_child_of_rotate_point = tmp_node;

    create_node(8);
    tree->root->left->right->right = tmp_node;
    tmp_node->parent = tree->root->left->right;

    tree->left_rotate(rotate_point);

    ASSERT_TRUE(tree->root->left == right_child_of_rotate_point) << "Left of root value: " << tree->root->left->value << "; which is should be: " << right_child_of_rotate_point->value;
    ASSERT_TRUE(right_child_of_rotate_point->left == rotate_point);
    ASSERT_TRUE(rotate_point->right == left_child_of_right_child_of_rotate_point) << "Right of rotate point value: " << rotate_point->right->value << "; which is should be: " << left_child_of_right_child_of_rotate_point->value;

    // check root when it is rotated to another node
    tree->left_rotate(tree->root);
    ASSERT_TRUE(tree->root->value == 15);

    this->checkParent(tree->root);
    this->checkIsBinarySeachTree(tree->root);
}

TEST_F(RedBlackTreeTest, RotateRight)
{

    /*
        * Test rotate right
        *     10
        *    /  \
        *   5   15
        *  /    / \
        * 3    12  20
        *     / \
        *    6   8
        *
        * After rotate right
        *       10
        *      /  \
        *     5   12
        *    /   / \
        *   3   6  15
        *         / \
        *        8  20

    */

    create_node(10);
    tree->root = tmp_node;
    RedBlackTree::IndividualNode<int> *rotate_point;
    RedBlackTree::IndividualNode<int> *left_child_of_rotate_point;
    RedBlackTree::IndividualNode<int> *right_child_of_left_child_of_rotate_point;

    create_node(5);
    tree->root->left = tmp_node;
    tmp_node->parent = tree->root;

    create_node(15);
    tree->root->right = tmp_node;
    tmp_node->parent = tree->root;
    rotate_point = tmp_node;

    create_node(3);
    tree->root->left->left = tmp_node;
    tmp_node->parent = tree->root->left;

    create_node(12);
    tree->root->right->left = tmp_node;
    tmp_node->parent = tree->root->right;
    left_child_of_rotate_point = tmp_node;

    create_node(6);
    tree->root->right->left->left = tmp_node;
    tmp_node->parent = tree->root->right->left;

    create_node(8);
    tree->root->right->left->right = tmp_node;
    tmp_node->parent = tree->root->right->left;
    right_child_of_left_child_of_rotate_point = tmp_node;

    create_node(20);
    tree->root->right->right = tmp_node;
    tmp_node->parent = tree->root->right;

    tree->right_rotate(rotate_point);

    ASSERT_TRUE(tree->root->right == left_child_of_rotate_point) << "Right of root value: " << tree->root->right->value << "; which is should be: " << left_child_of_rotate_point->value;
    ASSERT_TRUE(left_child_of_rotate_point->right == rotate_point);
    ASSERT_TRUE(rotate_point->left == right_child_of_left_child_of_rotate_point) << "Left of rotate point value: " << rotate_point->left->value << "; which is should be: " << right_child_of_left_child_of_rotate_point->value;

    // check root when it is rotated to another node
    tree->right_rotate(tree->root);
    ASSERT_TRUE(tree->root->value == 5);

    this->checkParent(tree->root);
    this->checkIsBinarySeachTree(tree->root);
}

TEST_F(RedBlackTreeTest, InsertTest)
{

    for (int i = 0; i < 50; ++i)
    {
        int randomValue = rand() % 100;
        create_node(randomValue);
        tree->insert(tmp_node);
        this->checkRedNodeNotHaveRedChild(tree->root);
        this->checkBlackPathLength();
        this->checkIsBinarySeachTree(tree->root);
    }
}

TEST_F(RedBlackTreeTest, BinaryTreeDeleteTest)
{
    /*
        * Test binary tree delete
        *     10
        *    /  \
        *   5   15
        *  / \    \
        * 3   7    20
        *    / \   /
        *   6   8  17
        *
        * After delete 7
        *       10
        *      /  \
        *     5   15
        *    / \    \
        *   3   8    20
        *      /    /
        *     6    17
        *
        * After delete 10
        *       15
        *      / \
        *     5   20
        *    / \  /
        *   3  8  17
        *

        */

    create_node(10);
    tree->root = tmp_node;
    auto node10 = tmp_node;

    create_node(5);
    tree->root->left = tmp_node;
    tmp_node->parent = tree->root;
    auto node5 = tmp_node;

    create_node(15);
    tree->root->right = tmp_node;
    tmp_node->parent = tree->root;

    create_node(3);
    tree->root->left->left = tmp_node;
    tmp_node->parent = tree->root->left;

    create_node(7);
    tree->root->left->right = tmp_node;
    tmp_node->parent = tree->root->left;
    auto node7 = tmp_node;

    create_node(20);
    tree->root->right->right = tmp_node;
    tmp_node->parent = tree->root->right;

    create_node(6);
    tree->root->left->right->left = tmp_node;
    tmp_node->parent = tree->root->left->right;

    create_node(8);
    tree->root->left->right->right = tmp_node;
    tmp_node->parent = tree->root->left->right;

    create_node(17);
    tree->root->right->right->left = tmp_node;
    tmp_node->parent = tree->root->right->right;

    // test the test itself :))
    this->checkIsBinarySeachTree(tree->root);

    // remove 7
    tree->binary_search_tree_delete(node7);
    std::cout << "After remove 7\n";
    std::cout << tree->bfsPrint() << "\n";
    ASSERT_EQ(node5->right->value, 8);

    this->checkParent(tree->root);
    this->checkIsBinarySeachTree(tree->root);

    // remove 10
    tree->binary_search_tree_delete(node10);
    std::cout << "After remove 10\n";
    std::cout << tree->bfsPrint() << "\n";

    this->checkParent(tree->root);
    this->checkIsBinarySeachTree(tree->root);
}

TEST_F(RedBlackTreeTest, DeleteTest)
{

    for (int i = 0; i < 8; ++i)
    {
        int randomValue = rand() % 100;
        create_node(randomValue);
        tree->insert(tmp_node);
        // test the test it self :))
        this->checkRedNodeNotHaveRedChild(tree->root);
        this->checkBlackPathLength();
        this->checkIsBinarySeachTree(tree->root);
    }

    std::cout<<"Original tree: "<<tree->bfsPrint()<<"\n";

    // now actually test the deletion
    for (int i = 0; i < 8; ++i)
    {
        std::cout<<"Deleting node number: "<<i<<" th\n";
        auto node = tree->get_random_node();
        std::cout<<"Node: "<<node->value<<" Root: "<<tree->root->value<<"\n";
        tree->remove(node);
        std::cout<<"After remove node tree: "<<tree->bfsPrint()<<"\n";
        this->checkIsBinarySeachTree(tree->root);
        this->checkBlackPathLength();
        this->checkRedNodeNotHaveRedChild(tree->root);
    }
}