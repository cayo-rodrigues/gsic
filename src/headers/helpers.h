#include <time.h>

unsigned int idigits(int n);

time_t now(void);
char *strnow(void);

char get_char(char *prompt);

void display_banner(char *msg);
void clear_screen();
void mkdir(char *path);

int mkdir_if_not_exists(char *path);
int is_dir(char *path);
int get_int(char *prompt);