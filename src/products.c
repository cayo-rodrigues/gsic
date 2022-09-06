#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "structs.h"
#include "products.h"
#include "tree.h"
#include "helpers.h"


double get_total_price(node *tree, double total)
{
    if (tree == NULL)
    {
        return 0;
    }
    total += get_total_price(tree->left, total) + get_total_price(tree->right, total);
    return total + (tree->product.price * tree->product.amount);
}

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

void print_row_sep(int sep_size)
{
    for (int i = 0; i < sep_size; i++)
    {
        printf("-");
    }
    printf("\n");
}

void print_row(product p, unsigned int col_size)
{
    int cols_count = 3;
    int sep_gap = 6;
    if (p.amount)
    {
        cols_count = 4;
        sep_gap = 9;
    }
    // print line separators (size of 3 or 4 columns + 6 or 9 because of the space taken by " | ")
    print_row_sep((col_size * cols_count) + sep_gap);

    // print product id
    printf("%i", p.id);

    // calculate how many digits in product id
    unsigned int digits = idigits(p.id);

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

    float price = p.price;

    if (p.amount)
    {
        // print product amount
        printf("x%i", p.amount);

        digits = idigits(p.amount);
        for (unsigned int i = 0; i < (col_size - digits) + 1; i++)
        {
            printf(" ");
        }
        printf(" | ");

        price = p.amount * price;
    }

    // print product price on the last column
    printf("R$ %.2f\n", price);
}

void print_header(char *headings[], unsigned int col_size, int col_count)
{
    for (int i = 0; i < col_count; i++)
    {
        // print heading name
        printf("%s", headings[i]);

        // print whitespace according to the length of heading name + 3 (because of the " | ")
        for (unsigned int j = 0; j < (col_size - strlen(headings[i])) + 3; j++)
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

void print_product(product p)
{
    printf("name: %s\n", p.name);
    printf("price: R$ %.2f\n", p.price);
    printf("amount: %i\n", p.amount);
    printf("--------------------------\n");
}

node *register_product(node *db_tree, node *customer_tree, int product_id)
{
    node *db_product = get_product(db_tree, product_id);
    if (db_product == NULL && product_id != 0)
    {
        printf("Invalid product id\n\n");
    }
    else if (product_id != 0)
    {
        node *p = get_product(customer_tree, product_id);
        if (p == NULL)
        {
            p = malloc(sizeof(node));
            p->product.id = db_product->product.id;
            p->product.price = db_product->product.price;
            p->product.amount = 1;
            strcpy(p->product.name, db_product->product.name);

            p->left = NULL;
            p->right = NULL;

            if (customer_tree == NULL)
            {
                customer_tree = p;
            }
            insert_node(customer_tree, p);

        }
        else
        {
            p->product.amount++;
        }

        print_product(p->product);
    }

    return customer_tree;
}

node *register_products(node *db_tree)
{
    node *customer_tree = NULL;
    int product_id = -1;

    while (product_id != 0) {
        printf("Product id: ");
        scanf("%i", &product_id);
        customer_tree = register_product(db_tree, customer_tree, product_id);
    };

    printf("\n");
    return customer_tree;
}