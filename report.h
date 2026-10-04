#ifndef REPORT_H
#define REPORT_H

#include <stdio.h>

struct Employee {
char name[50];
double baseSalary;
double bonus;
};

struct Budget {
char department[50];
double allocated;
double expenditure;
};

struct Supplier {
char supplierName[50];
char category[50];
};

struct Asset {
char assetName[50];
int quantity;
};

void employeeReport(struct Employee employees[], int count) {
double total = 0;
double highest = employees[0].baseSalary + employees[0].bonus;
double lowest = employees[0].baseSalary + employees[0].bonus;

printf("\n===== EMPLOYEE REPORT =====\n");
for(int i = 0; i < count; i++) {
double s = employees[i].baseSalary + employees[i].bonus;
printf("%s - N$ %.2f\n", employees[i].name, s);
total += s;
if(s > highest) highest = s;
if(s < lowest) lowest = s;
}
printf("Total: N$ %.2f\n", total);
printf("Average: N$ %.2f\n", total / count);
printf("Highest: N$ %.2f\n", highest);
printf("Lowest: N$ %.2f\n", lowest);
}

void budgetReport(struct Budget budgets[], int count) {
double allocated = 0;
double expenditure = 0;
int exceeded = 0;

for(int i = 0; i < count; i++) {
allocated += budgets[i].allocated;
expenditure += budgets[i].expenditure;
if(budgets[i].expenditure > budgets[i].allocated) exceeded++;
}
printf("\n===== BUDGET REPORT =====\n");
printf("Total Allocated: %.2f\n", allocated);
printf("Total Expenditure: %.2f\n", expenditure);
printf("Remaining: %.2f\n", allocated - expenditure);
printf("Budgets Exceeded: %d\n", exceeded);
}

void supplierReport(struct Supplier suppliers[], int count) {
printf("\n===== SUPPLIER REPORT =====\n");
for(int i = 0; i < count; i++) {
printf("%d. %s - %s\n", i+1, suppliers[i].supplierName, suppliers[i].category);
}
}

void assetReport(struct Asset assets[], int count) {
printf("\n===== ASSET REPORT =====\n");
for(int i = 0; i < count; i++) {
printf("%d. %s - %d units\n", i+1, assets[i].assetName, assets[i].quantity);
}
}

#endif