#include "gtest/gtest.h"
#include "evolution/population/red_black_tree.h"

#include "iostream"

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
}

TEST_F(RedBlackTreeTest, RotateRight)
{

    /*
        * Test rotate right
        *     10
        *    /  \
        *   5   15
        *  /    / \
        * 3    7  20
        *     / \
        *    6   8
        *
        * After rotate right
        *       10
        *      /  \
        *     5   7
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

    create_node(7);
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
}

TEST_F(RedBlackTreeTest, InsertTest)
{

    for (int i = 0; i < 50; ++i)
    {
        int randomValue = rand() % 100;
        create_node(randomValue);
        tree->insert(tmp_node);
        std::cout << "Step" << i << ":\n"
                  << tree->bfsPrint();
        checkRedNodeNotHaveRedChild(tree->root);
    }
}
