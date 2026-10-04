/* employees.h - Employee Management module */

#ifndef EMPLOYEES_H
#define EMPLOYEES_H

#define MAX_EMPLOYEES 100

void employeeMenu(void);
void addEmployee(void);
void displayEmployees(void);
void searchEmployee(void);
void showSalaryDetails(void);
void displayOneEmployee(int index);

int findEmployeeById(char id[]);
double calculateGrossSalary(double basic, double housing, double transport);
double calculateTax(double gross);
double calculatePension(double basic);
double calculateNetSalary(double gross, double tax, double pension);

/* used by the reports module */
int getEmployeeCount(void);
double getEmployeeGross(int index);
void getEmployeeName(int index, char name[]);

#endif
