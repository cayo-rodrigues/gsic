#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// self made header files
#include "structs.h"
#include "tree.h"
#include "products.h"
#include "helpers.h"

// global variables
const char *PRODUCTS_DB_PATH = "./src/db/products.csv";
const int STR_MAX_LEN = 64;
const int TABLE_COLS = 3;
unsigned int LONGEST_STR = 3;

// function prototypes
node *read_db(node *tree, FILE *fp);


int main(void)
{
    clear_screen();

    FILE *fp = fopen(PRODUCTS_DB_PATH, "r");
    if (fp == NULL)
    {
        printf("Could not read file\n");
        return 1;
    }

    node *db_tree = NULL;

    // read products database and organize data in a binary tree
    db_tree = read_db(db_tree, fp);
    if (db_tree == NULL)
    {
        printf("Out of memory\n");
        return 1;
    }

    fclose(fp);

    // get tree balance
    balance balance = get_balance(db_tree);

    // balance the tree if needed
    if (balance.rate > 1)
        db_tree = balance_tree(db_tree, balance);

    // char *headings[3] = {"id", "name", "price"};
    // print_header(headings, LONGEST_STR, 3);
    // display_products(db_tree, LONGEST_STR);

    printf("(Input 0 to finish)\n\n");
    node *customer_tree = register_products(db_tree);

    if (customer_tree == NULL)
    {
        display_banner("Goodbye, hope you enjoyed GSiC :(");
        return 1;
    }

    balance = get_balance(customer_tree);
    if (balance.rate > 1)
        customer_tree = balance_tree(customer_tree, balance);

    clear_screen();

    char *purchase_dt = strnow();
    printf("Purchased on %s\n", purchase_dt);

    char *customer_headings[4] = {"id", "name", "amount", "price"};
    print_header(customer_headings, LONGEST_STR, 4);
    display_products(customer_tree, LONGEST_STR);

    double purchase_total_price = get_total_price(customer_tree, 0.00);
    printf("\nTotal price: R$ %.2f\n", purchase_total_price);

    printf("\nGenerate receipt? (Y/n)\n");

    display_banner("Thank you for buying with us! :D");

    free_tree(db_tree);
    free_tree(customer_tree);
}


// read a csv database pointed to by `fp` and return the data in a binary tree
node *read_db(node *tree, FILE *fp)
{
    // each string retrieved by fscanf
    char str[STR_MAX_LEN];
    // determines if fscanf found a pattern or not
    int result;

    int col_index = 0;
    char *row_info[TABLE_COLS];

    int row_index = 0;

    do {
        // accept 63 bytes long strings, but reject commas and line breaks
        result = fscanf(fp, "%63[^,\n]", str);

        // when hitting a comma or line break
        if (result == 0)
        {
            // skip them
            fscanf(fp, "%*c");
        }
        else if (result == 1)
        {
            row_info[col_index] = malloc(sizeof(str));
            strcpy(row_info[col_index], str);

            // proceed to the next column
            col_index++;

            // when reaching the last column of a row
            if (col_index == TABLE_COLS)
            {
                // skip header row
                if (row_index != 0)
                {
                    // build binary tree on the fly
                    node *n = build_node(tree, row_info);

                    // on the first loop, tree get it's root node
                    if (row_index == 1)
                    {
                        tree = n;
                    }

                    insert_node(tree, n);

                    // remember the longest product name
                    unsigned int str_len = strlen(n->product.name);
                    if (str_len > LONGEST_STR)
                    {
                        LONGEST_STR = str_len;
                    }
                }

                // reset to first column
                col_index = 0;
                // proceed to next row
                row_index++;

                for (int i = 0; i < TABLE_COLS; i++)
                {
                    free(row_info[i]);
                }
            }
        }
    } while (result != EOF);

    return tree;
}