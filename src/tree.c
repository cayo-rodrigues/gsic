#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "structs.h"
#include "tree.h"

extern const int TABLE_COLS;


// recursively free all nodes of a tree
void free_tree(node *root)
{
    if (root == NULL)
    {
        return;
    }
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}


// balance a binary tree, moving it's root as closest to the middle as possible
node *balance_tree(node *tree, balance balance)
{
    node *tmp = tree;
    if (balance.left_height > balance.right_height)
    {
        // move to the middle of the tree outer left branch
        for (int i = 0; i < balance.rate / 2; i++)
        {
            tmp = tmp->left;
            tmp->right = tree;
            tree->left = NULL;
            tree = tmp;
        }
    }
    else
    {
        // move to the middle of the tree outer right branch
        for (int i = 0; i < balance.rate / 2; i++)
        {
            tmp = tmp->right;
            tmp->left = tree;
            tree->right = NULL;
            tree = tmp;
        }
    }

    return tree;
}


// recursively count how many nodes a tree has in it's outer branches,
// either left (direction = 0) or right (direction = 1)
int count_nodes(node *tree, int diretion)
{
    if (tree == NULL)
    {
        return 0;
    }

    return diretion == 0
        ? count_nodes(tree->left, diretion) + 1
        : count_nodes(tree->right, diretion) + 1;
}


// return the overral balance of a tree, that is, how many nodes it has on both sides,
// and the difference between it's two outer branches
balance get_balance(node *tree)
{
    balance balance;
    balance.left_height = count_nodes(tree, 0) - 1;
    balance.right_height = count_nodes(tree, 1) - 1;
    balance.rate = abs(balance.left_height - balance.right_height);

    return balance;
}


// recursively looks for an appropriated place to insert a node in a tree,
// using binary search algorithm
int insert_node(node *root, node *node)
{
    if (root == NULL)
    {
        return 1;
    }

    if (node->product.id < root->product.id)
    {
        if (insert_node(root->left, node))
        {
            root->left = node;
        }
    }
    else if (node->product.id > root->product.id)
    {
        if (insert_node(root->right, node))
        {
            root->right = node;
        }
    }

    return 0;
}


// build a node to be inserted in a tree, and return it
node *build_node(node *tree, char *node_info[TABLE_COLS])
{
    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
        free_tree(tree);
        return NULL;
    }

    n->product.id = atoi(node_info[0]);
    n->product.price = atof(node_info[2]);
    strcpy(n->product.name, node_info[1]);

    n->left = NULL;
    n->right = NULL;

    return n;
}