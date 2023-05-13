#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Employee {
    int id;
    char name[100];
    int age;
    float salary;
    char job_title[100];
};

void addEmployee(struct Employee *employees, int *count, FILE *file) {
    if (*count >= 100) {
        printf("Employee database is full. Cannot add more employees.\n");
        return;
    }

    struct Employee newEmployee;

    printf("Enter employee details:\n");
    printf("Employee ID: ");
    scanf("%d", &newEmployee.id);
    printf("Employee Name: ");
    scanf(" %[^\n]", newEmployee.name);
    printf("Employee Age: ");
    scanf("%d", &newEmployee.age);
    printf("Employee Salary: ");
    scanf("%f", &newEmployee.salary);
    printf("Enter employee job title: ");
    scanf(" %[^\n]", newEmployee.job_title);

    employees[*count] = newEmployee;
    (*count)++;

    fprintf(file, "%d,%s,%d,%.2f,%s\n", newEmployee.id, newEmployee.name, newEmployee.age, newEmployee.salary, newEmployee.job_title);

    printf("Employee added successfully.\n");
}

void updateEmployee(struct Employee *employees, int count, FILE *file) {
    int employeeId;
    int found = 0;

    printf("Enter the employee ID to update: ");
    scanf("%d", &employeeId);

    for (int i = 0; i < count; i++) {
        if (employees[i].id == employeeId) {
            printf("Enter new details for the employee:\n");
            printf("Employee Name: ");
            scanf(" %[^\n]", employees[i].name);
            printf("Employee Age: ");
            scanf("%d", &employees[i].age);
            printf("Employee Salary: ");
            scanf("%f", &employees[i].salary);
            printf("Employee job title: ");
            scanf(" %[^\n]", employees[i].job_title);

            printf("Employee details updated successfully.\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Employee not found.\n");
    } else {
        // Rewrite all employee data to the file
        fclose(file);
        file = fopen("employees.txt", "w");
        for (int i = 0; i < count; i++) {
            fprintf(file, "%d,%s,%d,%.2f,%s\n", employees[i].id, employees[i].name, employees[i].age, employees[i].salary, employees[i].job_title);
        }
        fclose(file);
    }
}

void deleteEmployee(struct Employee *employees, int *count, FILE *file) {
    int employeeId;
    int found = 0;

    printf("Enter the employee ID to delete: ");
    scanf("%d", &employeeId);

    for (int i = 0; i < *count; i++) {
        if (employees[i].id == employeeId) {
            for (int j = i; j < *count - 1; j++) {
                employees[j] = employees[j + 1];
            }

            (*count)--;
            printf("Employee deleted successfully.\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Employee not found.\n");
    } else {
        // Rewrite all employee data to the file
        fclose(file);
        file = fopen("employees.txt", "w");
        for (int i = 0; i < *count; i++) {
            fprintf(file, "%d,%s,%d,%.2f,%s\n", employees[i].id, employees[i].name, employees[i].age, employees[i].salary, employees[i].job_title);
        }
        fclose(file);
    }
}

void displayEmployees(struct Employee *employees, int count) {
    if (count == 0) {
        printf("Employee database is empty.\n");
        return;
    }

    printf("Employee Database:\n");
    printf("ID\tName\tAge\tSalary\tJob title\n");
    for (int i = 0; i < count; i++) {
        printf("%d\t%s\t%d\t%.2f\t%s\n", employees[i].id, employees[i].name, employees[i].age, employees[i].salary, employees[i].job_title);
    }
}

int main() {
    struct Employee employees[100];
    int count = 0;
    int choice;

    printf("Employee Management System\n");

    // Open the file for reading and writing
    FILE *file = fopen("employees.txt", "a+");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return 1;
    }

    // Load existing employee data from the file
    char line[255];
    while (fgets(line, sizeof(line), file)) {
        struct Employee newEmployee;
        sscanf(line, "%d,%[^,],%d,%f,%[^\n]", &newEmployee.id, newEmployee.name, &newEmployee.age, &newEmployee.salary, newEmployee.job_title);
        employees[count] = newEmployee;
        count++;
    }

    while (1) {
        printf("\nSelect an option:\n");
        printf("1. Add an employee\n");
        printf("2. Update an employee\n");
        printf("3. Delete an employee\n");
        printf("4. Display employees\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addEmployee(employees, &count, file);
                break;
            case 2:
                updateEmployee(employees, count, file);
                break;
            case 3:
                deleteEmployee(employees, &count, file);
                break;
            case 4:
                displayEmployees(employees, count);
                break;
            case 5:
                printf("Exiting Employee Management System. Goodbye!\n");
                fclose(file);
                return 0;
            default:
                printf("Invalid choice. Please select a valid option.\n");
        }
    }
    return 0;
}

