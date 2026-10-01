// budget.h
#ifndef BUDGET_H
#define BUDGET_H

#define MAX_DEPARTMENTS 20


///declaring variable//////
typedef struct {
    char name[100];
    double allocated;
    double expenditure;
    double remaining;
} Department;



void enterBudgets(Department dept[], int number);
void displayBudgets(Department dept[], int number);
void calculateRemaining(Department dept[], int number);
void checkStatus(Department dept[], int number);

#endif
