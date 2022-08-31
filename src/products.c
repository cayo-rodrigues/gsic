#include <stdio.h>
#include <string.h>

#include "structs.h"
#include "products.h"

void display_products(node *root, unsigned int col_size)
{
    if (root == NULL)
    {
        return;
    }
    display_products(root->left, col_size);
    print_row(root->product, col_size);
    display_products(root->right, col_size);
}

void print_row(product p, unsigned int col_size)
{
    // print line separators (size of 3 columns + 6 because of the space taken by " | ")
    for (unsigned int i = 0; i < (col_size * 3) + 6; i++)
    {
        printf("-");
    }
    printf("\n");

    // print product id
    printf("%i", p.id);

    // calculate how many digits in product id
    unsigned int digits = 0;
    unsigned int n = p.id;
    do {
        n /= 10;
        digits++;
    } while (n != 0);

    // print whitespace accordingly (this makes all columns have the same width)
    for (unsigned int i = 0; i < (col_size - digits); i++)
    {
        printf(" ");
    }
    printf(" | ");

    // print product name
    printf("%s", p.name);

    // print whitespace according to the length of product name
    for (unsigned int i = 0; i < (col_size - strlen(p.name)); i++)
    {
        printf(" ");
    }
    printf(" | ");

    // print product price on the last column
    printf("R$ %.2f\n", p.price);
}

void print_header(char *headings[3], unsigned int col_size)
{
    for (int i = 0; i < 3; i++)
    {
        // print heading name
        printf("%s", headings[i]);

        // print whitespace according to the length of heading name + 3 (because of the " | ")
        for (unsigned int j = 0; j < (col_size - strlen(headings[i]) + 3); j++)
        {
            printf(" ");
        }
    }
    printf("\n");
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