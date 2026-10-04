#ifndef EMPLOYEES_H
#define EMPLOYEES_H

typedef struct {
    int id;
    char name[50];
    char department[50];
    float basicSalary;
    float housingAllowance;
    float transportAllowance;
} Employee;

// Function prototypes
void addEmployee(Employee employees[], int *count);

#endif