#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// self made header files
#include "structs.h"
#include "tree.h"
#include "products.h"

// global variables
const char *PRODUCTS_DB_PATH = "src/db/products.csv";
const int TABLE_COLS = 3;
const int STR_MAX_LEN = 64;

// function prototypes
node *read_db(node *tree, FILE *fp);


int main(int argc, char *argv[])
{
    FILE *fp = fopen(PRODUCTS_DB_PATH, "r");
    if (fp == NULL)
    {
        printf("Could not read file\n");
        return 1;
    }

    node *tree = NULL;

    // read products database and organize data in a binary tree
    tree = read_db(tree, fp);
    if (tree == NULL)
    {
        printf("Out of memory\n");
        return 1;
    }

    fclose(fp);

    // get tree balance
    balance balance = get_balance(tree);

    // balance the tree if needed
    if (balance.rate > 1)
        tree = balance_tree(tree, balance);

    display_products(tree);
    free_tree(tree);
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

                    if (row_index == 1)
                    {
                        tree = n;
                    }

                    insert_node(tree, n);
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
