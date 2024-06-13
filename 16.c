#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "employees.dat"

typedef struct {
    int id;
    char name[100];
    int age;
    float salary;
} Employee;

void addEmployee() {
    FILE *file = fopen(FILENAME, "ab");
    if (!file) {
        perror("Unable to open file");
        exit(EXIT_FAILURE);
    }

    Employee emp;
    printf("Enter Employee ID: ");
    scanf("%d", &emp.id);
    printf("Enter Employee Name: ");
    scanf("%s", emp.name);
    printf("Enter Employee Age: ");
    scanf("%d", &emp.age);
    printf("Enter Employee Salary: ");
    scanf("%f", &emp.salary);

    fwrite(&emp, sizeof(Employee), 1, file);
    fclose(file);

    printf("Employee added successfully.\n");
}

void displayEmployees() {
    FILE *file = fopen(FILENAME, "rb");
    if (!file) {
        perror("Unable to open file");
        exit(EXIT_FAILURE);
    }

    Employee emp;
    printf("%-10s %-30s %-5s %-10s\n", "ID", "Name", "Age", "Salary");
    printf("------------------------------------------------------------\n");

    while (fread(&emp, sizeof(Employee), 1, file)) {
        printf("%-10d %-30s %-5d %-10.2f\n", emp.id, emp.name, emp.age, emp.salary);
    }

    fclose(file);
}

void searchEmployee() {
    FILE *file = fopen(FILENAME, "rb");
    if (!file) {
        perror("Unable to open file");
        exit(EXIT_FAILURE);
    }

    int id;
    printf("Enter Employee ID to search: ");
    scanf("%d", &id);

    Employee emp;
    while (fread(&emp, sizeof(Employee), 1, file)) {
        if (emp.id == id) {
            printf("Employee found:\n");
            printf("ID: %d\n", emp.id);
            printf("Name: %s\n", emp.name);
            printf("Age: %d\n", emp.age);
            printf("Salary: %.2f\n", emp.salary);
            fclose(file);
            return;
        }
    }

    printf("Employee with ID %d not found.\n", id);
    fclose(file);
}

int main() {
    int choice;

    while (1) {
        printf("\nEmployee Management System\n");
        printf("1. Add Employee\n");
        printf("2. Display All Employees\n");
        printf("3. Search Employee by ID\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addEmployee();
                break;
            case 2:
                displayEmployees();
                break;
            case 3:
                searchEmployee();
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
