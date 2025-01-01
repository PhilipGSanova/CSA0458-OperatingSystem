#include <stdio.h>
#include <windows.h>

#define SHM_SIZE 1024 // Size of the shared memory segment

int main() {
    // Create a named shared memory segment
    HANDLE hMapFile = CreateFileMapping(
        INVALID_HANDLE_VALUE,   // Use the system paging file
        NULL,                   // Default security attributes
        PAGE_READWRITE,         // Read/write access
        0,                      // Maximum object size (high-order 32 bits)
        SHM_SIZE,               // Size of the shared memory region
        "SharedMemoryExample"); // Name of the mapping object

    if (hMapFile == NULL) {
        printf("Could not create file mapping object. Error code: %d\n", GetLastError());
        return 1;
    }

    // Map the shared memory segment to the address space of the process
    LPCTSTR pBuf = (LPTSTR)MapViewOfFile(
        hMapFile,           // Handle to the mapping object
        FILE_MAP_ALL_ACCESS, // Read/write permission
        0,                   // High-order 32 bits of the file offset
        0,                   // Low-order 32 bits of the file offset
        SHM_SIZE);           // Number of bytes to map

    if (pBuf == NULL) {
        printf("Could not map view of file. Error code: %d\n", GetLastError());
        CloseHandle(hMapFile);
        return 1;
    }

    // Write data to the shared memory
    strcpy((char *)pBuf, "Hello, shared memory!");

    // Print the data written to the shared memory
    printf("Data written to shared memory: %s\n", pBuf);

    // Unmap the shared memory
    UnmapViewOfFile(pBuf);

    // Close the file mapping object handle
    CloseHandle(hMapFile);

    return 0;
}
