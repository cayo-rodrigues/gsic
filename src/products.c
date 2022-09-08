#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "structs.h"
#include "products.h"
#include "tree.h"
#include "helpers.h"

extern const int TABLE_COLS;


// recursively calculate the total price of a products tree
double get_total_price(node *tree, double total)
{
    if (tree == NULL)
    {
        return 0;
    }
    total += get_total_price(tree->left, total) + get_total_price(tree->right, total);
    return total + (tree->product.price * tree->product.amount);
}


// print a line to be the separator of rows in a table
void print_row_sep(int sep_size)
{
    for (int i = 0; i < sep_size; i++)
    {
        printf("-");
    }
    printf("\n");
}

// print whitespaces according to `gap_size` + a " | " in the end
// (this makes all columns have the same width)
void print_row_gap(int gap_size)
{
    for (int i = 0; i < gap_size; i++)
    {
        printf(" ");
    }
    printf(" | ");
}


// print one row of a products tree table
void print_row(product p, unsigned int col_size)
{
    int cols_count = p.amount ? TABLE_COLS + 1 : TABLE_COLS;
    int sep_gap = 3 * (cols_count - 1);

    // print line separators (size of 3 or 4 columns + 6 or 9 because of the space taken by " | ")
    print_row_sep((col_size * cols_count) + sep_gap);

    // print product id
    printf("%i", p.id);

    // print whitespace according to number of digits in product id
    print_row_gap(col_size - idigits(p.id));

    // print product name
    printf("%s", p.name);

    // print whitespace according to the length of product name
    print_row_gap(col_size - strlen(p.name));

    float price = p.price;

    if (p.amount)
    {
        // print product amount
        printf("x%i", p.amount);

        // print whitespace according to number of digits in product amount
        print_row_gap(col_size - idigits(p.amount));

        price = p.amount * price;
    }

    // print product price on the last column
    printf("R$ %.2f\n", price);
}


// recursively display a products tree as a table
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


// print the table header of a products tree table
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


// retrieves one product from a products tree, recursively using binary search algorithm
node *get_product(node *tree, unsigned int product_id)
{
    if (tree == NULL)
    {
        return NULL;
    }

    if (product_id < tree->product.id)
    {
        return get_product(tree->left, product_id);
    }
    else if (product_id > tree->product.id)
    {
        return get_product(tree->right, product_id);
    }
    
    return tree;
}


// print one product from a products tree
void print_product(product p)
{
    printf("name: %s\n", p.name);
    printf("price: R$ %.2f\n", p.price);
    printf("amount: %i\n", p.amount);
    printf("--------------------------\n");
}


// add one product to a customer's products tree
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


// use a loop to register many products in a customer's products tree
node *register_products(node *db_tree)
{
    node *customer_tree = NULL;
    int product_id;
    do {
        product_id = get_int("Product id: ");
        customer_tree = register_product(db_tree, customer_tree, product_id);
    } while (product_id != 0);

    printf("\n");
    return customer_tree;
}