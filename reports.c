#include <stdio.h>
#include "reports.h"
#include "employees.h"
#include "budgets.h"
#include "suppliers.h"
#include "assets.h"
#include "input.h"

void reportsMenu(void)
{
    int choice;

    do
    {
        printf("\n========== REPORTS ==========\n");
        printf("1. Employee report\n");
        printf("2. Budget report\n");
        printf("3. Supplier report\n");
        printf("4. Asset report\n");
        printf("5. All reports\n");
        printf("6. Back to main menu\n");
        choice = readInt("Enter your choice: ", 1, 6);

        switch (choice)
        {
            case 1:
                employeeReport();
                break;
            case 2:
                budgetReport();
                break;
            case 3:
                supplierReport();
                break;
            case 4:
                assetReport();
                break;
            case 5:
                displayAllReports();
                break;
            case 6:
                printf("Returning to main menu...\n");
                break;
        }
    } while (choice != 6);
}

/* recursive function: adds up the gross salary of employee index and all before it */
double totalSalaries(int index)
{
    if (index < 0)
    {
        return 0;
    }
    return getEmployeeGross(index) + totalSalaries(index - 1);
}

void employeeReport(void)
{
    int count = getEmployeeCount();
    int i;
    int highestIndex = 0;
    int lowestIndex = 0;
    double total;
    char highestName[50];
    char lowestName[50];

    printf("\n========== EMPLOYEE REPORT ==========\n");

    if (count == 0)
    {
        printf("Total Employees: 0\n");
        printf("No employee data to report.\n");
        return;
    }

    /* find the highest and lowest gross salary */
    for (i = 1; i < count; i++)
    {
        if (getEmployeeGross(i) > getEmployeeGross(highestIndex))
        {
            highestIndex = i;
        }
        if (getEmployeeGross(i) < getEmployeeGross(lowestIndex))
        {
            lowestIndex = i;
        }
    }

    total = totalSalaries(count - 1);
    getEmployeeName(highestIndex, highestName);
    getEmployeeName(lowestIndex, lowestName);

    printf("Total Employees : %d\n", count);
    printf("Total Payroll   : N$%.2f\n", total);
    printf("Average Salary  : N$%.2f\n", total / count);
    printf("Highest Salary  : N$%.2f (%s)\n", getEmployeeGross(highestIndex), highestName);
    printf("Lowest Salary   : N$%.2f (%s)\n", getEmployeeGross(lowestIndex), lowestName);
    printf("(Salaries shown are gross monthly salaries.)\n");
}

void budgetReport(void)
{
    int count = getDepartmentCount();
    int i;
    int overCount = 0;
    double totalAllocated = 0;
    double totalSpent = 0;
    double allocated;
    double spent;
    char name[50];

    printf("\n========== BUDGET REPORT ==========\n");

    if (count == 0)
    {
        printf("No budget data to report.\n");
        return;
    }

    printf("%-20s %15s %15s %15s  %s\n", "Department", "Allocated", "Spent", "Remaining", "Status");
    printLine();
    for (i = 0; i < count; i++)
    {
        allocated = getAllocatedBudget(i);
        spent = getExpenditure(i);
        getDepartmentName(i, name);

        totalAllocated = totalAllocated + allocated;
        totalSpent = totalSpent + spent;

        printf("%-20s %15.2f %15.2f %15.2f  ", name, allocated, spent, calculateRemainingBudget(allocated, spent));
        if (isWithinBudget(allocated, spent))
        {
            printf("WITHIN BUDGET\n");
        }
        else
        {
            printf("OVER BUDGET\n");
            overCount++;
        }
    }
    printLine();

    printf("Total Allocated Budget : N$%.2f\n", totalAllocated);
    printf("Total Expenditure      : N$%.2f\n", totalSpent);
    printf("Remaining Budget       : N$%.2f\n", calculateRemainingBudget(totalAllocated, totalSpent));
    printf("Departments over budget: %d\n", overCount);

    if (overCount > 0)
    {
        displayExceededDepartments();
    }
}

void supplierReport(void)
{
    printf("\n========== SUPPLIER REPORT ==========\n");
    displaySuppliers();
}

void assetReport(void)
{
    int count = getAssetCount();
    int i;
    int type;
    int typeCount[NUMBER_OF_TYPES] = {0};
    double typeValue[NUMBER_OF_TYPES] = {0};
    double totalValue = 0;
    char typeName[50];

    printf("\n========== ASSET REPORT ==========\n");
    displayAssets();

    if (count == 0)
    {
        return;
    }

    /* count assets and add up values for each type */
    for (i = 0; i < count; i++)
    {
        type = getAssetTypeNumber(i);
        typeCount[type]++;
        typeValue[type] = typeValue[type] + getAssetValue(i);
        totalValue = totalValue + getAssetValue(i);
    }

    printf("\nSummary by type:\n");
    for (i = 0; i < NUMBER_OF_TYPES; i++)
    {
        getAssetTypeName(i, typeName);
        printf("  %-17s %3d asset(s)   N$%.2f\n", typeName, typeCount[i], typeValue[i]);
    }
    printf("Total value of all assets: N$%.2f\n", totalValue);
}

void displayAllReports(void)
{
    employeeReport();
    budgetReport();
    supplierReport();
    assetReport();
}
