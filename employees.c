
#include <stdio.h>

typedef struct {
    int id;
    char name[50];
    char department[50];
    float basicSalary;
    float housingAllowance;
    float transportAllowance;
} Employee;

// Function to add an employee
void addEmployee(Employee employees[], int *count) {
    printf("Enter Employee ID: ");
    scanf("%d", &employees[*count].id);

    printf("Enter Name: ");
    scanf("%49s", employees[*count].name);

    printf("Enter Department: ");
    scanf("%49s", employees[*count].department);

    printf("Enter Basic Salary: ");
    scanf("%f", &employees[*count].basicSalary);

    printf("Enter Housing Allowance: ");
    scanf("%f", &employees[*count].housingAllowance);

    printf("Enter Transport Allowance: ");
    scanf("%f", &employees[*count].transportAllowance);

    (*count)++;

    printf("\nEmployee added successfully!\n");
}

int main(void) {
    Employee employees[50];
    int count = 0;

    addEmployee(employees, &count);

    printf("\nTotal employees: %d\n", count);

    return 0;
}