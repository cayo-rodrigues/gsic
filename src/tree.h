void print_tree(node* root);
void free_tree(node* root);

int count_nodes(node *tree, int diretion);
int insert_node(node *root, node *node);

balance get_balance(node* tree);

node *balance_tree(node *tree, balance balance);
node *build_node(node *tree, char *node_info[]);