#include <stdio.h>

int main(void) {
    char s[100];

    /* Scan for name input */
    printf("Enter your name: ");
    scanf("%99s", s);

    /* Print with inputted name */
    printf("hello, %s!\n", s);

    return 0;
}