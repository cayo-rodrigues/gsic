void generate_receipt(node *products_tree, char *date, double total_price);
void insert_receipt_row(FILE *fp, product p);

int user_wants_receipt(void);