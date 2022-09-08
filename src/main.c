// external libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// self made header files
#include "headers/structs.h"
#include "headers/receipts.h"
#include "headers/tree.h"
#include "headers/products.h"
#include "headers/helpers.h"
#include "headers/db.h"

// global variables
extern const char *PRODUCTS_DB_PATH;
extern const int STR_MAX_LEN;
extern const int TABLE_COLS;
extern char *RECEIPTS_DIR_PATH;
extern unsigned int LONGEST_STR;


int main(void)
{
    clear_screen();

    // open products db file for reading
    FILE *fp = fopen(PRODUCTS_DB_PATH, "r");
    if (fp == NULL)
    {
        printf("Could not read file\n");
        return 1;
    }

    // read products db and organize data in a binary tree
    node *db_tree = read_db(NULL, fp);
    if (db_tree == NULL)
    {
        printf("Out of memory\n");
        return 1;
    }

    fclose(fp);

    // balance the tree if needed, centering it's root
    balance balance = get_balance(db_tree);
    if (balance.rate > 1)
        db_tree = balance_tree(db_tree, balance);

    // prompt user to input products id's, building another tree
    printf("(Press Enter key or input 0 or any non-numeric character to finish)\n\n");
    node *customer_tree = register_products(db_tree);

    // in case user chooses no products
    if (customer_tree == NULL)
    {
        display_banner("Goodbye, hope you enjoyed GSiC :(");
        return 1;
    }

    // balance user tree as needed
    balance = get_balance(customer_tree);
    if (balance.rate > 1)
        customer_tree = balance_tree(customer_tree, balance);

    clear_screen();

    // get and display current date and time
    char *purchase_dt = strnow();
    printf("Purchased on %s\n", purchase_dt);

    // show products user has bought in a table
    char *customer_headings[4] = {"id", "name", "amount", "price"};
    print_header(customer_headings, LONGEST_STR, 4);
    display_products(customer_tree, LONGEST_STR);

    // get and display purchase total price
    double purchase_total_price = get_total_price(customer_tree, 0.00);
    printf("\nTotal price: R$ %.2f\n\n", purchase_total_price);

    // generate receipt txt file if user desires it
    if (user_wants_receipt())
    {
        generate_receipt(customer_tree, purchase_dt, purchase_total_price);
        printf("\n");
    }

    // free the memory allocated from the heap for both trees
    free_tree(db_tree);
    free_tree(customer_tree);

    display_banner("Thank you for buying with us! :D");
}
