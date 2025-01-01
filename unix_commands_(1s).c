#include <stdio.h>
#include <string.h>

int main() {
    char fn[100], pat[100], temp[200];
    FILE *fp;

    printf("\nEnter file name: ");
    scanf("%s", fn);

    printf("Enter the pattern: ");
    scanf("%s", pat);

    fp = fopen(fn, "r");
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }

    printf("\nLines containing the pattern '%s':\n", pat);

    while (fgets(temp, sizeof(temp), fp)) {
        if (strstr(temp, pat) != NULL) { // Check if pattern exists in the line
            printf("%s", temp);
        }
    }

    fclose(fp);
    return 0;
}