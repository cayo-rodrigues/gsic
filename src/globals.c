const char *PRODUCTS_DB_PATH = "./src/db/products.csv";
char *RECEIPTS_DIR_PATH = "./receipts/";

const int TABLE_COLS = 3;
const int STR_MAX_LEN = 64;
unsigned int LONGEST_STR = 3;

#ifdef _WIN32
    const char *CLEAR_SCREEN_COMMAND = "cls";
#else
    const char *CLEAR_SCREEN_COMMAND = "clear";
#endif