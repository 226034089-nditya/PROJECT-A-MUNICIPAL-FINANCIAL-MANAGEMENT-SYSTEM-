#include <stdio.h>
#include <stdlib.h>
#include "employees.h"
#include "budget.h"
#include "suppliers.h"
#include "assets.h"
#include "reports.h"


//1-Global arrays 
Employee employees[50];
Budget budgets[20];
Supplier suppliers[50];
Asset assets[50];
int employeeCount = 0;
int budgetCount = 0;
int supplierCount = 0;
int assetCount = 0;


//2-Select choice from menu
void displayMainMenu() {
 printf("\n========================================\n");
 printf("MUNICIPAL FINANCIAL MANAGEMENT SYSTEM\n");
 printf("========================================\n");
 printf("1. Employee Management\n");
 printf("2. Budget Management\n");
 printf("3. Supplier Management\n");
 printf("4. Asset Management\n");
 printf("5. Reports\n");
 printf("6. Exit\n");
 printf("Enter your choice: ");
}
//3-Employee Management
void employeeMenu() {
 int choice;
 
 while (1) {
 printf("\n--- EMPLOYEE MANAGEMENT ---\n");
 printf("1. Add Employee\n");
 printf("2. Display Employees\n");
 printf("3. Search Employee\n");
 printf("4. Back to Main Menu\n");
 printf("Enter your choice: ");
 scanf("%d", &choice);
 getchar();
 
 
 switch (choice) {
 case 1:
 addEmployee(employees, &employeeCount);
 break;
 case 2:
 displayEmployees(employees, employeeCount);
 break;
 case 3:
 searchEmployee(employees, employeeCount);
 break;
 case 4:
 return;
 default:
 printf("Invalid choice. Please try again.\n");
 }
 }
}

//4-Budget management
void budgetMenu() {
 int choice;
 while (1) {
 printf("\n--- BUDGET MANAGEMENT ---\n");
 printf("1. Add Budget\n");
 printf("2. Display Budgets\n");
 printf("3. Check Exceeded Budgets\n");
 printf("4. Back to Main Menu\n");
 printf("Enter your choice: ");
 scanf("%d", &choice);
 getchar();
 
 switch (choice) {
 case 1:
 addBudget(budgets, &budgetCount);
 break;
 case 2:
 displayBudgets(budgets, budgetCount);
 break;
 case 3:
 checkExceededBudgets(budgets, budgetCount);
 break;
 case 4:
 return;
 default:
 printf("Invalid choice. Please try again.\n");
 }
 }
}

//5- Supplier management
void supplierMenu() {
 int choice;
 while (1) {
 printf("\n--- SUPPLIER MANAGEMENT ---\n");
 printf("1. Add Supplier\n");
 printf("2. Display Suppliers\n");
 printf("3. Search Supplier\n");
 printf("4. Back to Main Menu\n");
 printf("Enter your choice: ");
 scanf("%d", &choice);
 getchar();
 
 switch (choice) {
 case 1:
 addSupplier(suppliers, &supplierCount);
 break;
 case 2:
 displaySuppliers(suppliers, supplierCount);
 break;
 case 3:
 searchSupplier(suppliers, supplierCount);
 break;
 case 4:
 return;
 default:
 printf("Invalid choice. Please try again.\n");
 }
 }
}
//5-Asset management
void assetMenu() {
 int choice;
 while (1) {
 printf("\n--- ASSET MANAGEMENT ---\n");
 printf("1. Add Asset\n");
 printf("2. Display Assets\n");
 printf("3. Search Asset\n");
 printf("4. Back to Main Menu\n");
 printf("Enter your choice: ");
 scanf("%d", &choice);
 getchar();
 
 switch (choice) {
 case 1:
 addAsset(assets, &assetCount);
 break;
 case 2:
 displayAssets(assets, assetCount);
 break;
 case 3:
 searchAsset(assets, assetCount);
 break;
 case 4:
 return;
 default:
 printf("Invalid choice. Please try again.\n");
 }
 }
}

//6- reports
void reportsMenu() {
 int choice;
 
 while (1) {
 printf("\n--- REPORTS ---\n");
 printf("1. Employee Report\n");
 printf("2. Budget Report\n");
 printf("3. Supplier Report\n");
 printf("4. Asset Report\n");
 printf("5. Back to Main Menu\n");
 printf("Enter your choice: ");
 scanf("%d", &choice);
 getchar();
 
 switch (choice) {
 case 1:
 displayEmployeeReport(employees, employeeCount);
 break;
 case 2:
 displayBudgetReport(budgets, budgetCount);
 break;
 case 3:
 displaySupplierReport(suppliers, supplierCount);
 break;
 case 4:
 displayAssetReport(assets, assetCount);
 break;
 case 5:
 return;
 default:
 printf("Invalid choice. Please try again.\n");
 }
 }
}

int main() {
 int mainChoice;
 
 while (1) {
 displayMainMenu();
 scanf("%d", &mainChoice);
 getchar();
 
 switch (mainChoice) {
 case 1:
 employeeMenu();
 break;
 case 2:
 budgetMenu();
 break;
 case 3:
 supplierMenu();
 break;
 case 4:
 assetMenu();
 break;
 case 5:
 reportsMenu();
 break;
 case 6:
 printf("\nThank you for using our MFMS. See you next time!\n");
 exit(0);
 default:
 printf("Invalid choice. Please try again.\n");
 }
 }
 
 return 0;
}