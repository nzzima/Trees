#include "pch.h"
#include "OptimalBinaryTree.hpp"

TEST(OptimalBinaryTreeTests, Test_TRUE_Search)
{
    int keyCount = 7;
    int k[]{ 0, 1, 2, 3, 4, 5, 6 };
    int p[]{ 6, 2, 8, 1, 7, 4, 3 };
    int pCount = 7;
    int q[]{ 0, 0, 0, 0, 0, 0, 0, 0 };

    OptimalBinaryTree<int> Tree(k, keyCount, p, pCount, q);
    Tree.PrintTree();
	
    EXPECT_TRUE(Tree.Search(0));
    EXPECT_TRUE(Tree.Search(1));
    EXPECT_TRUE(Tree.Search(2));
    EXPECT_TRUE(Tree.Search(3));
    EXPECT_TRUE(Tree.Search(4));
}


TEST(OptimalBinaryTreeTests, Test_FALSE_Search)
{
    int keyCount = 7;
    int k[]{ 0, 1, 2, 3, 4, 5, 6 };
    int p[]{ 6, 2, 8, 1, 7, 4, 3 };
    int pCount = 7;
    int q[]{ 0, 0, 0, 0, 0, 0, 0, 0 };

    OptimalBinaryTree<int> Tree(k, keyCount, p, pCount, q);
    Tree.PrintTree();

    EXPECT_FALSE(Tree.Search(7));
    EXPECT_FALSE(Tree.Search(8));
    EXPECT_FALSE(Tree.Search(9));
    EXPECT_FALSE(Tree.Search(-1));
    EXPECT_FALSE(Tree.Search(-2));
}

TEST(OptimalBinaryTreeTests, Test_with_Success_Failure)
{
    int keyCount = 7;
    int k[]{ 0, 1, 2, 3, 4, 5, 6 };
    int p[]{ 6, 2, 8, 1, 7, 4, 3 };
    int pCount = 7;
    int q[]{ 3, 4, 1, 5, 8, 2, 6, 7 };

    OptimalBinaryTree<int> Tree(k, keyCount, p, pCount, q);

    Tree.PrintTree();
}