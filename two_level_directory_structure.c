#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char mainDirectory[] = "C:/Users/itssk/OneDrive/Desktop"; 
    char subDirectory[] = "os";
    char fileName[] = "example.txt";
    char filePath[200];
    char mainDirPath[200];

    // Build the directory path
    snprintf(mainDirPath, sizeof(mainDirPath), "%s/%s/", mainDirectory, subDirectory);
    
    // Concatenate file name to the directory path
    snprintf(filePath, sizeof(filePath), "%s%s", mainDirPath, fileName);

    // Open the file for writing
    FILE *file = fopen(filePath, "w");
    if (file == NULL) {
        printf("Error creating file.\n");
        return 1;
    }

    // Write content to the file
    fprintf(file, "This is an example file content.");

    // Close the file
    fclose(file);

    // Print success message with file path
    printf("File created successfully: %s\n", filePath);

    return 0;
}
