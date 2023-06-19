#include <unistd.h>
#include <stdio.h>

#define BUFFER_SIZE 1024

int main() 
{
    char *str;
    int a = read(0, str, 2);
    printf("->>>>%d\n", a);
    printf("%s\n", str);
}
