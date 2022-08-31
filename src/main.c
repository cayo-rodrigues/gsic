#include <stdio.h>

const char *PRODUCTS_DB_PATH = "src/db/products.csv";

int main(int argc, char *argv[])
{
    FILE *fp = fopen(PRODUCTS_DB_PATH, "r");
    if (fp == NULL)
    {
        printf("Could not read file");
        return 1;
    }

    fclose(fp);
}