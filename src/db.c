#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "headers/structs.h"
#include "headers/tree.h"

extern const char *PRODUCTS_DB_PATH;
extern const int STR_MAX_LEN;
extern const int TABLE_COLS;
extern unsigned int LONGEST_STR;


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
        // scan file reading between commas and line breaks
        result = fscanf(fp, "%127[^,\n]", str);

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