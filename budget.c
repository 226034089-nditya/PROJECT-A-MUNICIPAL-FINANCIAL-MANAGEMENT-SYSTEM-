/* budget.c - Budget Management module
   Keeps the allocated budget and the expenditure for each department. */

#include <stdio.h>
#include <string.h>
#include "budget.h"
#include "input.h"

char deptName[MAX_DEPARTMENTS][TEXT_SIZE];
double deptAllocated[MAX_DEPARTMENTS];
double deptSpent[MAX_DEPARTMENTS];
int departmentCount = 0;

void budgetMenu(void)
{
    int choice;

    do
    {
        printf("\n========== BUDGET MANAGEMENT ==========\n");
        printf("1. Enter departmental budget\n");
        printf("2. Enter expenditure\n");
        printf("3. Display budget information\n");
        printf("4. Show departments over budget\n");
        printf("5. Back to main menu\n");
        choice = readInt("Enter your choice: ", 1, 5);

        switch (choice)
        {
            case 1:
                addDepartmentBudget();
                break;
            case 2:
                enterExpenditure();
                break;
            case 3:
                displayBudgets();
                break;
            case 4:
                displayExceededDepartments();
                break;
            case 5:
                printf("Returning to main menu...\n");
                break;
        }
    } while (choice != 5);
}

void addDepartmentBudget(void)
{
    char name[TEXT_SIZE];
    double amount;
    int index;

    printf("\n--- Enter Departmental Budget ---\n");
    readString("Department name: ", name, TEXT_SIZE);
    index = findDepartment(name);

    if (index != -1)
    {
        /* department already exists so we just update its budget */
        printf("Department %s already has a budget of N$%.2f.\n", deptName[index], deptAllocated[index]);
        amount = readMoney("Enter the new allocated budget (N$): ");
        deptAllocated[index] = amount;
        printf("Budget for %s updated.\n", deptName[index]);
        return;
    }

    if (departmentCount >= MAX_DEPARTMENTS)
    {
        printf("Sorry, no more departments can be added.\n");
        return;
    }

    amount = readMoney("Allocated budget (N$): ");

    strcpy(deptName[departmentCount], name);
    deptAllocated[departmentCount] = amount;
    deptSpent[departmentCount] = 0;
    departmentCount++;

    printf("Budget for %s saved.\n", name);
}

void enterExpenditure(void)
{
    char name[TEXT_SIZE];
    double amount;
    int index;

    if (departmentCount == 0)
    {
        printf("No departments yet. Enter a departmental budget first.\n");
        return;
    }

    printf("\n--- Enter Expenditure ---\n");
    readString("Department name: ", name, TEXT_SIZE);
    index = findDepartment(name);

    if (index == -1)
    {
        printf("Department %s was not found.\n", name);
        return;
    }

    amount = readMoney("Amount spent (N$): ");
    while (amount == 0)
    {
        printf("  Error: expenditure must be more than 0.\n");
        amount = readMoney("Amount spent (N$): ");
    }

    deptSpent[index] = deptSpent[index] + amount;
    printf("Expenditure recorded.\n");

    if (!isWithinBudget(deptAllocated[index], deptSpent[index]))
    {
        printf("WARNING: %s has now exceeded its budget!\n", deptName[index]);
    }

    displayOneBudget(index);
}

void displayOneBudget(int index)
{
    double remaining = calculateRemainingBudget(deptAllocated[index], deptSpent[index]);

    printf("\nDepartment       : %s\n", deptName[index]);
    printf("Allocated Budget : N$%.2f\n", deptAllocated[index]);
    printf("Expenditure      : N$%.2f\n", deptSpent[index]);
    printf("Remaining Budget : N$%.2f\n", remaining);

    if (isWithinBudget(deptAllocated[index], deptSpent[index]))
    {
        printf("Status           : WITHIN BUDGET\n");
    }
    else
    {
        printf("Status           : OVER BUDGET\n");
    }
}

void displayBudgets(void)
{
    int i;

    if (departmentCount == 0)
    {
        printf("No budgets have been entered yet.\n");
        return;
    }

    printf("\n--- Budget Information ---\n");
    for (i = 0; i < departmentCount; i++)
    {
        displayOneBudget(i);
    }
}

void displayExceededDepartments(void)
{
    int i;
    int count = 0;

    printf("\n--- Departments Over Budget ---\n");
    for (i = 0; i < departmentCount; i++)
    {
        if (!isWithinBudget(deptAllocated[i], deptSpent[i]))
        {
            printf("%-20s over by N$%.2f\n", deptName[i], deptSpent[i] - deptAllocated[i]);
            count++;
        }
    }

    if (count == 0)
    {
        printf("No department has exceeded its budget.\n");
    }
}

/* returns the position of the department in the arrays, or -1 if not found */
int findDepartment(char name[])
{
    int i;

    for (i = 0; i < departmentCount; i++)
    {
        if (sameText(deptName[i], name))
        {
            return i;
        }
    }
    return -1;
}

/* this is the function that calculates the budget balance */
double calculateRemainingBudget(double allocated, double spent)
{
    return allocated - spent;
}

/* returns 1 if spending is within the budget, 0 if it is over */
int isWithinBudget(double allocated, double spent)
{
    if (spent <= allocated)
    {
        return 1;
    }
    return 0;
}

int getDepartmentCount(void)
{
    return departmentCount;
}

double getAllocatedBudget(int index)
{
    return deptAllocated[index];
}

double getExpenditure(int index)
{
    return deptSpent[index];
}

void getDepartmentName(int index, char name[])
{
    strcpy(name, deptName[index]);
}
