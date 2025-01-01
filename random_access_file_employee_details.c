#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Employee {
    int empId;
    char empName[50];
    float empSalary;
};

int main() {
    FILE *filePtr;
    struct Employee emp;
    
    // Open file in read/write binary mode, create it if it doesn't exist
    filePtr = fopen("employee.dat", "rb+");
    if (filePtr == NULL) {
        filePtr = fopen("employee.dat", "wb+");
        if (filePtr == NULL) {
            printf("Error creating the file.\n");
            return 1;
        }
    }
    
    int choice;
    do {
        printf("\nEmployee Database Menu:\n");
        printf("1. Add Employee\n");
        printf("2. Display Employee Details\n");
        printf("3. Update Employee Details\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: // Add Employee
                printf("Enter Employee ID: ");
                scanf("%d", &emp.empId);
                printf("Enter Employee Name: ");
                scanf("%s", emp.empName);
                printf("Enter Employee Salary: ");
                scanf("%f", &emp.empSalary);
                
                fseek(filePtr, (emp.empId - 1) * sizeof(struct Employee), SEEK_SET);
                fwrite(&emp, sizeof(struct Employee), 1, filePtr);
                printf("Employee details added successfully.\n");
                break;
            
            case 2: // Display Employee Details
                printf("Enter Employee ID to display: ");
                int displayId;
                scanf("%d", &displayId);
                
                fseek(filePtr, (displayId - 1) * sizeof(struct Employee), SEEK_SET);
                if (fread(&emp, sizeof(struct Employee), 1, filePtr) == 1) {
                    printf("Employee ID: %d\n", emp.empId);
                    printf("Employee Name: %s\n", emp.empName);
                    printf("Employee Salary: %.2f\n", emp.empSalary);
                } else {
                    printf("Employee with ID %d not found.\n", displayId);
                }
                break;
            
            case 3: // Update Employee Details
                printf("Enter Employee ID to update: ");
                int updateId;
                scanf("%d", &updateId);
                
                fseek(filePtr, (updateId - 1) * sizeof(struct Employee), SEEK_SET);
                if (fread(&emp, sizeof(struct Employee), 1, filePtr) == 1) {
                    printf("Enter New Employee Name: ");
                    scanf("%s", emp.empName);
                    printf("Enter New Employee Salary: ");
                    scanf("%f", &emp.empSalary);
                    
                    fseek(filePtr, (updateId - 1) * sizeof(struct Employee), SEEK_SET);
                    fwrite(&emp, sizeof(struct Employee), 1, filePtr);
                    printf("Employee details updated successfully.\n");
                } else {
                    printf("Employee with ID %d not found.\n", updateId);
                }
                break;
            
            case 4: // Exit
                printf("Exiting the program.\n");
                break;
            
            default: // Invalid choice
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 4);
    
    fclose(filePtr);
    return 0;
}
