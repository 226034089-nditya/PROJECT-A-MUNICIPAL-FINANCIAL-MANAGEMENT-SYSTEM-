/* budget.h - Budget Management module */

#ifndef BUDGET_H
#define BUDGET_H

#define MAX_DEPARTMENTS 30

void budgetMenu(void);
void addDepartmentBudget(void);
void enterExpenditure(void);
void displayBudgets(void);
void displayExceededDepartments(void);
void displayOneBudget(int index);

int findDepartment(char name[]);
double calculateRemainingBudget(double allocated, double spent);
int isWithinBudget(double allocated, double spent);

/* used by the reports module */
int getDepartmentCount(void);
double getAllocatedBudget(int index);
double getExpenditure(int index);
void getDepartmentName(int index, char name[]);

#endif
