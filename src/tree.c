#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "structs.h"
#include "tree.h"

const int TABLE_COLUMNS = 3;


void print_tree(node *root)
{
    if (root == NULL)
    {
        return;
    }
    print_tree(root->left);

    printf("%i\n", root->product.id);
    printf("%s\n", root->product.name);
    printf("%.2f\n", root->product.price);
    printf("----------------------\n");

    print_tree(root->right);
}

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

balance get_balance(node *tree)
{
    balance balance;
    balance.left_height = count_nodes(tree, 0) - 1;
    balance.right_height = count_nodes(tree, 1) - 1;
    balance.rate = abs(balance.left_height - balance.right_height);

    return balance;
}

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

// returns true(1) when finding an empty space, false(0) otherwise
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

node *build_node(node *tree, char *node_info[TABLE_COLUMNS])
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