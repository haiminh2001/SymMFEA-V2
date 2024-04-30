#include "gtest/gtest.h"
#include "evolution/population/red_black_tree.h"

class RedBlackTreeTest : public ::testing::Test {
protected:
    RedBlackTree::RedBlackTree<int> *tree;

    void SetUp() override {
        tree = new RedBlackTree::RedBlackTree<int>();
    }

    void TearDown() override {
        delete tree;
    }
};

TEST_F(RedBlackTreeTest, InsertAndFindTest) {
    

    RedBlackTree::IndividualNode<int>* node = new RedBlackTree::IndividualNode<int>(1);
    tree->insert(node);

    ASSERT_TRUE(tree->num_nodes == 1);
    // tree->insert(individual2);

    // ASSERT_TRUE(tree->find(individual1));
    // ASSERT_TRUE(tree->find(individual2));
}

// TEST_F(RedBlackTreeTest, RemoveTest) {
//     int individual1 = 1;
//     int individual2 = 2;

//     tree->insert(individual1);
//     tree->insert(individual2);

//     tree->remove(individual1);

//     ASSERT_FALSE(tree->find(individual1));
//     ASSERT_TRUE(tree->find(individual2));
// }