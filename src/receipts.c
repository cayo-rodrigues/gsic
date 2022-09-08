#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "headers/structs.h"
#include "headers/helpers.h"

extern char *RECEIPTS_DIR_PATH;
extern unsigned int LONGEST_STR;


// return 1 if user wants to generate a receipt, 0 otherwise
int user_wants_receipt(void)
{
    char answer;
    do {
        answer = get_char("Generate receipt? (Y/n) ");
    } while (answer != 'y' && answer != 'n' && answer != '\n');
    printf("\n");
    return (answer == 'y' || answer == '\n');
}


// insert one receipt product row in a receipt file
void insert_receipt_row(FILE *fp, product p)
{
    int gap = (LONGEST_STR - (strlen(p.name) + idigits(p.amount))) + 7;

    fprintf(fp, "%s X%i", p.name, p.amount);
    for (int i = 0; i < gap; i++)
    {
        fprintf(fp, ".");
    }
    fprintf(fp, "R$ %.2f\n", p.price * p.amount);
}


// recursively insert product rows in a receipt file
void fill_receipt(FILE *fp, node *root)
{
    if (root == NULL)
    {
        return;
    }
    fill_receipt(fp, root->left);
    insert_receipt_row(fp, root->product);
    fill_receipt(fp, root->right);
}


// generate and format receipt txt file
void generate_receipt(node *products_tree, char *date, double total_price)
{
    long int seconds = now();
    char *buf = malloc((strlen(RECEIPTS_DIR_PATH)) + 12 + idigits(seconds) + 1);
    sprintf(buf, "%sreceipt_%li.txt", RECEIPTS_DIR_PATH, seconds);

    mkdir_if_not_exists(RECEIPTS_DIR_PATH);

    FILE *fp = fopen(buf, "w");

    fprintf(fp, "GSiC\n\n");
    fprintf(fp, "Purchased on %s\n", date);
    fprintf(fp, "Products: \n\n");

    fill_receipt(fp, products_tree);

    fprintf(fp, "\nTotal: R$ %.2f\n", total_price);

    printf("Receipt file generated at %s\n", buf);

    fclose(fp);
    free(buf);
}