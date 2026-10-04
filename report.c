#include <stdio.h>

int main() {
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

struct Employee employees[3] = {
{"Alice", 15000.0, 2000.0},
{"Bob", 12000.0, 1500.0},
{"Charlie", 18000.0, 2500.0}
};
int employeeCount = 3;

struct Budget budgets[2] = {
{"IT", 50000.0, 45000.0},
{"HR", 20000.0, 22000.0}
};
int budgetCount = 2;

struct Supplier suppliers[2] = {
{"Supplier A", "Tech Supplies"},
{"Supplier B", "Office Furniture"}
};

struct Asset assets[2] = {
{"Laptops", 15},
{"Desks", 30}
};

int choice = 0;
do {
printf("\n--- Reports ---\n");
printf("1. Employee Report\n");
printf("2. Budget Report\n");
printf("3. Supplier Report\n");
printf("4. Asset Report\n");
printf("5. Back / Exit\n");
printf("Enter choice: ");
scanf("%d", &choice);

if (choice == 1) {
double total = 0;
double highest = employees[0].baseSalary + employees[0].bonus;
double lowest = employees[0].baseSalary + employees[0].bonus;

for(int i = 0; i < employeeCount; i++) {
double totalSalary = employees[i].baseSalary + employees[i].bonus;
total += totalSalary;
if(totalSalary > highest) highest = totalSalary;
if(totalSalary < lowest) lowest = totalSalary;
}
printf("\n===== EMPLOYEE REPORT =====\n");
for(int i = 0; i < employeeCount; i++) {
printf("%s - N$ %.2f\n", employees[i].name, employees[i].baseSalary + employees[i].bonus);
}
printf("Total Salary: N$ %.2f\n", total);
printf("Average Salary: N$ %.2f\n", total / employeeCount);
printf("Highest Salary: N$ %.2f\n", highest);
printf("Lowest Salary: N$ %.2f\n", lowest);
}
else if (choice == 2) {
printf("\n===== BUDGET REPORT =====\n");
double allocated = 0.0;
double expenditure = 0.0;
int exceeded = 0;
for (int i = 0; i < budgetCount; i++) {
allocated += budgets[i].allocated;
expenditure += budgets[i].expenditure;
if ((budgets[i].allocated - budgets[i].expenditure) < 0) {
exceeded++;
}
}
printf("Total Allocated: %.2f\n", allocated);
printf("Total Expenditure: %.2f\n", expenditure);
printf("Remaining: %.2f\n", allocated - expenditure);
printf("Budgets Exceeded: %d\n", exceeded);
}
else if (choice == 3) {
printf("\n===== SUPPLIER REPORT =====\n");
for(int i = 0; i < 2; i++) {
printf("%d. %s - %s\n", i+1, suppliers[i].supplierName, suppliers[i].category);
}
}
else if (choice == 4) {
printf("\n===== ASSET REPORT =====\n");
for(int i = 0; i < 2; i++) {
printf("%d. %s - %d units\n", i+1, assets[i].assetName, assets[i].quantity);
}
}

} while (choice!= 5);

printf("Exiting...\n");
return 0;
}