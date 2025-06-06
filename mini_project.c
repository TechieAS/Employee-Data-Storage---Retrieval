#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "employees.txt"

struct employee
{
    int id;
    char name[50];
    char designation[100];
    float salary;
};

void displayEmployees()
{
    FILE *file = fopen(FILENAME, "r");
    struct employee emp;

    if (file == NULL)
    {
        perror("Error opening file");
        return;
    }

    printf("\nEmployee Records:\n");
    while (fread(&emp, sizeof(struct employee), 1, file))
    {
        printf("ID: %d | Name: %s | Designation: %s | Salary: %.2f\n",
               emp.id, emp.name, emp.designation, emp.salary);
    }
    fclose(file);
}

void saveToFile(struct employee emp, const char *mode)
{
    FILE *file = fopen(FILENAME, mode);
    if (file == NULL)
    {
        perror("Error opening file.");
        return;
    }

    fwrite(&emp, sizeof(struct employee), 1, file);
    fclose(file);
}

int main()
{
    struct employee emp;
    int choice;

    do
    {
        printf("\n1. Add Employee\n");
        printf("2. Display All Employees\n");
        printf("3. Exit Program\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter Employee ID: ");
            scanf("%d", &emp.id);
            printf("Enter Employee Name: ");
            scanf(" %49s", emp.name);
            printf("Enter Employee Designation: ");
            scanf(" %99s", emp.designation);
            printf("Enter Employee Salary: ");
            scanf("%f", &emp.salary);
            saveToFile(emp, "a");
            printf("Employee added successfully.\n");
            break;
        case 2:
            displayEmployees();
            break;
        case 3:
            printf("Exiting program...\n");
            return 0;
        default:
            printf("Invalid choice, please try again.\n");
        }
    } while (choice != 3);

    return 0;
}