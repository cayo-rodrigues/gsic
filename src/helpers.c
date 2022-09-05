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

char *strnow(void)
{
    time_t dt = time(NULL);
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