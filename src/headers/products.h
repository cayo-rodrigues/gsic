void display_products(node *root, unsigned int col_size);
void print_header(char *headings[3], unsigned int col_size, int col_count);

node *register_products(node *db_tree);

double get_total_price(node *tree, double total);