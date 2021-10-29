#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    char s[100];
    int randN;
    int i;
    
    /* Seed rand */
    srand(time(0));

    /* Scan for name input */
    printf("Enter your name: ");
    scanf("%99s", s);

    /* Random int between 1 and 10 */
    randN = (int)(((float)rand() / RAND_MAX) * 10) + 1;

    /* Print hello, <name>! (even) or hi there, <name>! (odd), randN times */
    for (i = 0; i < randN; i++) {
        if (randN % 2 == 0) {
            printf("%d: hello, %s!\n", randN, s);
        }
        else {
            printf("%d: hi there, %s!\n", randN, s);
        }
    }
    return 0;
}