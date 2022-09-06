#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int idigits(int n)
{
    unsigned int digits = 0;
    do {
        n /= 10;
        digits++;
    } while (n != 0);

    return digits;
}

time_t now(void)
{
    return time(NULL);
}

char *strnow(void)
{
    time_t dt = now();
    return ctime(&dt);
}

void print_banner_border(int str_len)
{
    for (int i = 0; i < str_len + 3; i++)
    {
        printf("*");
    }
    printf("\n\n");
}

void display_banner(char *msg)
{
    int str_len = strlen(msg);
    printf("\n");
    print_banner_border(str_len);
    printf("%s\n\n", msg);
    print_banner_border(str_len);
}

void clear_screen(void)
{
    system("clear");
}

char get_char(char *prompt)
{
    char c;
    printf("%s", prompt);
    scanf(" %c", &c);
    return c;
}

void mkdir(char *path)
{
    char *buf = malloc((sizeof path) + 6 + 1);
    sprintf(buf, "mkdir %s", path);
    system(buf);
    free(buf);
}

int is_dir(char *path)
{
    FILE *dp = fopen(path, "r");
    int result = 1;
    if (dp == NULL)
    {
        result = 0;
    }
    fclose(dp);
    return result;
}

int mkdir_if_not_exists(char *path)
{
    if (is_dir(path))
    {
        return 0;
    }
    mkdir(path);
    return 1;
}