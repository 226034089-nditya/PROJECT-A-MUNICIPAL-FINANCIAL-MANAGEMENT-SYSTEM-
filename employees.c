/* employees.c - Employee Management module
   Stores employees in arrays. Index i in every array belongs to the same employee. */

#include <stdio.h>
#include <string.h>
#include "employees.h"
#include "input.h"

#define PENSION_RATE 0.07

char empId[MAX_EMPLOYEES][10];
char empName[MAX_EMPLOYEES][TEXT_SIZE];
char empDepartment[MAX_EMPLOYEES][TEXT_SIZE];
char empPosition[MAX_EMPLOYEES][TEXT_SIZE];
double empBasic[MAX_EMPLOYEES];
double empHousing[MAX_EMPLOYEES];
double empTransport[MAX_EMPLOYEES];
int employeeCount = 0;

void employeeMenu(void)
{
    int choice;

    do
    {
        printf("\n========== EMPLOYEE MANAGEMENT ==========\n");
        printf("1. Add employee\n");
        printf("2. Display all employees\n");
        printf("3. Search for an employee\n");
        printf("4. Calculate employee salary\n");
        printf("5. Back to main menu\n");
        choice = readInt("Enter your choice: ", 1, 5);

        switch (choice)
        {
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
                showSalaryDetails();
                break;
            case 5:
                printf("Returning to main menu...\n");
                break;
        }
    } while (choice != 5);
}

void addEmployee(void)
{
    char id[10];
    char firstName[TEXT_SIZE];
    char surname[TEXT_SIZE];
    char fullName[TEXT_SIZE * 2];

    if (employeeCount >= MAX_EMPLOYEES)
    {
        printf("Sorry, the employee list is full.\n");
        return;
    }

    printf("\n--- Add New Employee ---\n");

    /* the ID must not already be used */
    readString("Employee ID (e.g. E001): ", id, 10);
    while (findEmployeeById(id) != -1)
    {
        printf("  Error: employee ID %s already exists.\n", id);
        readString("Employee ID (e.g. E001): ", id, 10);
    }

    readString("First name: ", firstName, TEXT_SIZE);
    readString("Surname: ", surname, TEXT_SIZE);

    /* join first name and surname into one full name */
    strcpy(fullName, firstName);
    strcat(fullName, " ");
    strcat(fullName, surname);
    while (strlen(fullName) >= TEXT_SIZE)
    {
        printf("  Error: full name is too long, please use shorter names.\n");
        readString("First name: ", firstName, TEXT_SIZE);
        readString("Surname: ", surname, TEXT_SIZE);
        strcpy(fullName, firstName);
        strcat(fullName, " ");
        strcat(fullName, surname);
    }

    strcpy(empId[employeeCount], id);
    strcpy(empName[employeeCount], fullName);
    readString("Department: ", empDepartment[employeeCount], TEXT_SIZE);
    readString("Position/Job title: ", empPosition[employeeCount], TEXT_SIZE);

    empBasic[employeeCount] = readMoney("Basic salary (N$): ");
    while (empBasic[employeeCount] == 0)
    {
        printf("  Error: basic salary must be more than 0.\n");
        empBasic[employeeCount] = readMoney("Basic salary (N$): ");
    }
    empHousing[employeeCount] = readMoney("Housing allowance (N$): ");
    empTransport[employeeCount] = readMoney("Transport allowance (N$): ");

    employeeCount++;
    printf("Employee %s added successfully. Total employees: %d\n", fullName, employeeCount);
}

void displayEmployees(void)
{
    int i;
    double gross;

    if (employeeCount == 0)
    {
        printf("No employees have been added yet.\n");
        return;
    }

    printf("\n%-8s %-22s %-16s %-16s %14s\n", "ID", "Name", "Department", "Position", "Gross (N$)");
    printLine();
    for (i = 0; i < employeeCount; i++)
    {
        gross = calculateGrossSalary(empBasic[i], empHousing[i], empTransport[i]);
        printf("%-8s %-22s %-16s %-16s %14.2f\n", empId[i], empName[i], empDepartment[i], empPosition[i], gross);
    }
    printLine();
    printf("Total employees: %d\n", employeeCount);
}

/* prints all the details of one employee including the salary calculation */
void displayOneEmployee(int index)
{
    double gross = calculateGrossSalary(empBasic[index], empHousing[index], empTransport[index]);
    double tax = calculateTax(gross);
    double pension = calculatePension(empBasic[index]);
    double net = calculateNetSalary(gross, tax, pension);

    printf("\nEmployee ID         : %s\n", empId[index]);
    printf("Name                : %s\n", empName[index]);
    printf("Department          : %s\n", empDepartment[index]);
    printf("Position            : %s\n", empPosition[index]);
    printf("Basic salary        : N$%.2f\n", empBasic[index]);
    printf("Housing allowance   : N$%.2f\n", empHousing[index]);
    printf("Transport allowance : N$%.2f\n", empTransport[index]);
    printf("Gross salary        : N$%.2f\n", gross);
    printf("Tax (PAYE)          : N$%.2f\n", tax);
    printf("Pension (7%%)        : N$%.2f\n", pension);
    printf("Net salary          : N$%.2f\n", net);
}

void searchEmployee(void)
{
    int choice;
    int index;
    int i;
    int found = 0;
    char searchText[TEXT_SIZE];

    if (employeeCount == 0)
    {
        printf("No employees have been added yet.\n");
        return;
    }

    printf("\nSearch by:\n");
    printf("1. Employee ID\n");
    printf("2. Name\n");
    printf("3. Department\n");
    choice = readInt("Enter your choice: ", 1, 3);

    if (choice == 1)
    {
        readString("Enter employee ID: ", searchText, TEXT_SIZE);
        index = findEmployeeById(searchText);
        if (index == -1)
        {
            printf("No employee found with ID %s.\n", searchText);
        }
        else
        {
            displayOneEmployee(index);
        }
    }
    else
    {
        readString("Enter text to search for: ", searchText, TEXT_SIZE);

        /* go through every employee and check if the text matches */
        for (i = 0; i < employeeCount; i++)
        {
            if ((choice == 2 && containsText(empName[i], searchText)) ||
                (choice == 3 && containsText(empDepartment[i], searchText)))
            {
                displayOneEmployee(i);
                found++;
            }
        }

        if (found == 0)
        {
            printf("No employees matched \"%s\".\n", searchText);
        }
        else
        {
            printf("\n%d employee(s) found.\n", found);
        }
    }
}

void showSalaryDetails(void)
{
    char id[10];
    int index;

    if (employeeCount == 0)
    {
        printf("No employees have been added yet.\n");
        return;
    }

    readString("Enter employee ID to calculate salary: ", id, 10);
    index = findEmployeeById(id);

    if (index == -1)
    {
        printf("No employee found with ID %s.\n", id);
    }
    else
    {
        displayOneEmployee(index);
    }
}

/* returns the position of the employee in the arrays, or -1 if not found */
int findEmployeeById(char id[])
{
    int i;

    for (i = 0; i < employeeCount; i++)
    {
        if (sameText(empId[i], id))
        {
            return i;
        }
    }
    return -1;
}

double calculateGrossSalary(double basic, double housing, double transport)
{
    return basic + housing + transport;
}

/* simplified monthly tax table used for this project */
double calculateTax(double gross)
{
    double rate;

    if (gross <= 5000)
    {
        rate = 0.0;
    }
    else if (gross <= 15000)
    {
        rate = 0.18;
    }
    else if (gross <= 30000)
    {
        rate = 0.25;
    }
    else
    {
        rate = 0.30;
    }

    return gross * rate;
}

double calculatePension(double basic)
{
    return basic * PENSION_RATE;
}

double calculateNetSalary(double gross, double tax, double pension)
{
    return gross - tax - pension;
}

int getEmployeeCount(void)
{
    return employeeCount;
}

double getEmployeeGross(int index)
{
    return calculateGrossSalary(empBasic[index], empHousing[index], empTransport[index]);
}

void getEmployeeName(int index, char name[])
{
    strcpy(name, empName[index]);
}
