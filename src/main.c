#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"

// global variables
const char *PRODUCTS_DB_PATH = "src/db/products.csv";
const int TABLE_COLS = 3;

void read_db(product list[], FILE *fp);


int main(int argc, char *argv[])
{
    FILE *fp = fopen(PRODUCTS_DB_PATH, "r");
    if (fp == NULL)
    {
        printf("Could not read file");
        return 1;
    }

    product products[8];

    read_db(products, fp);

    for (int i = 0; i < 8; i++)
    {
        printf("%i\n", products[i].id);
        printf("%s\n", products[i].name);
        printf("%.2f\n", products[i].price);
        printf("-----------------------\n");
    }

    fclose(fp);
}

void read_db(product list[], FILE *fp)
{
    // each string retrieved by fscanf
    char str[128];
    // determines if fscang found a pattern or not
    int result;

    // for iteration on each row columns
    int col_index = 0;
    char *row_info[TABLE_COLS];

    // for iteration on each product row
    int row_index = 0;

    do {
        // accept 127 bytes long strings, but reject commas and line breaks
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

            // when reaching the end of a row
            if (col_index == TABLE_COLS)
            {
                // skip header row
                if (row_index != 0)
                {
                    // set each product info
                    list[row_index - 1].id = atoi(row_info[0]);
                    list[row_index - 1].price = atof(row_info[2]);
                    strcpy(list[row_index - 1].name, row_info[1]);
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
}