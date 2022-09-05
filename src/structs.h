typedef struct product
{
    unsigned int id;
    char name[64];
    double price;
    unsigned int amount;
}
product;

typedef struct node
{
    product product;
    struct node *left;
    struct node *right;
}
node;

typedef struct balance
{
    int rate;
    int left_height;
    int right_height;
}
balance;