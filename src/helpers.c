#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

extern const int STR_MAX_LEN;

// return the number of digits of a given integer
unsigned int idigits(int n)
{
    unsigned int digits = 0;
    do {
        n /= 10;
        digits++;
    } while (n != 0);

    return digits;
}

// get current time in seconds since the EPOCH (1970-01-01)
time_t now(void)
{
    return time(NULL);
}

// get current time in a nice formated string
char *strnow(void)
{
    time_t dt = now();
    return ctime(&dt);
}

// print a line of size `str_len` with "*" characters, plus a final "\n\n"
void print_banner_border(int str_len)
{
    for (int i = 0; i < str_len + 3; i++)
    {
        printf("*");
    }
    printf("\n\n");
}

// display a nice banner with a message of your choice
void display_banner(char *msg)
{
    int str_len = strlen(msg);
    printf("\n");
    print_banner_border(str_len);
    printf("%s\n\n", msg);
    print_banner_border(str_len);
}


// clear the terminal screen
void clear_screen(void)
{
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}


// get an integer from the user, or 0 if an invalid character is given
int get_int(char *prompt)
{
    printf("%s", prompt);
    int size = idigits(INT_MAX) + 1;
    char buf[size];
    fgets(buf, size, stdin);
    return atoi(buf);
}


// get only one character from the user
char get_char(char *prompt)
{
    printf("%s", prompt);
    char c[STR_MAX_LEN];
    fgets(c, STR_MAX_LEN, stdin);
    return c[0];
}


// create a folder, or directory, at `path`
void mkdir(char *path)
{
    char *buf = malloc((sizeof path) + 6 + 1);
    sprintf(buf, "mkdir %s", path);
    system(buf);
    free(buf);
}


// return 1 if `path` is an existing directory, 0 otherwise
int is_dir(char *path)
{
    FILE *dp = fopen(path, "r");
    if (dp == NULL)
    {
        return 0;
    }
    fclose(dp);
    return 1;
}


// create a directory if it does not exist, returning 1 if created, 0 otherwise
int mkdir_if_not_exists(char *path)
{
    if (is_dir(path))
    {
        return 0;
    }
    mkdir(path);
    return 1;
}