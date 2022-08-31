#include <stdio.h>

#include "structs.h"
#include "products.h"

void display_products(node *root)
{
    if (root == NULL)
    {
        return;
    }
    display_products(root->left);

    printf("%i\n", root->product.id);
    printf("%s\n", root->product.name);
    printf("%.2f\n", root->product.price);
    printf("----------------------\n");

    display_products(root->right);
}

node *get_product(node *tree, unsigned int product_id)
{
    if (tree == NULL)
    {
        return NULL;
    }

    if (product_id < tree->product.id)
    {
        get_product(tree->left, product_id);
    }
    else if (product_id > tree->product.id)
    {
        get_product(tree->right, product_id);
    }
    else
    {
        return tree;
    }
}