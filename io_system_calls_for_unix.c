#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h> // For close()

extern int errno;

int main() {
    int fd = open("foo.txt", O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR);
    printf("fd = %d\n", fd);

    if (fd == -1) {
        printf("Error Number: %d\n", errno);
        perror("Program");
    } else {
        printf("File 'foo.txt' opened/created successfully.\n");
        close(fd); // Close the file descriptor
    }

    return 0;
}
