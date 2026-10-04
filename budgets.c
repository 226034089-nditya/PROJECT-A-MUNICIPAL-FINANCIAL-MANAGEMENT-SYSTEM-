#include <stdio.h>
#include <string.h>

#define MAX_DEPARTMENTS 10

/////Declaring Variable//////

typedef struct {

char name[100];

double allocated;

double expenditure;

double remaining;

} Department;

//////ask a user to enter departmentName/////

void enterBudgets(Department dept[], int number) {

for(int i = 0; i < number; i++) {

printf("\nEnter department name: ");

scanf("%s", dept[i].name);



/////ask a user to enter allocatedBudget/////

printf("Enter allocated budget for %s: ", dept[i].name);

scanf("%lf", &dept[i].allocated);



//////ask a user to enter Expenditure/////

printf("Enter expenditure for %s: ", dept[i].name);

scanf("%lf", &dept[i].expenditure);

}
}

/// to calculate the remainingBudget/////////

void calculateRemaining(Department dept[], int number) {

for(int i = 0; i < number; i++) {

dept[i].remaining = dept[i].allocated - dept[i].expenditure;

}
}

/////this to display the budget details///////

void displayBudgets(Department dept[], int number) {

printf("\nMUNICIPAL BUDGET SUMMARY\n");

printf("----------------------------\n");

for(int i = 0; i < number; i++) {

printf("Department: %s\n", dept[i].name);

printf("Allocated Budget: %.2f\n", dept[i].allocated);

printf("Expenditure: %.2f\n", dept[i].expenditure);

printf("Remaining Budget: %.2f\n", dept[i].remaining);

/////this is to check if expenditure is within the budget/////

if(dept[i].expenditure <= dept[i].allocated) {

printf("Status: WITHIN BUDGET\n");
} else {

printf("Status: EXCEEDED BUDGET\n");

}

printf("----------------------------\n");

}

}

//////thsi is to check if the expenditure exceeded the budget///////

void checkStatus(Department dept[], int number) {

printf("\nDepartments exceeding budget:\n");

for(int i = 0; i < number; i++) {

if(dept[i].expenditure > dept[i].allocated) {

printf("- %s (Exceeded by %.2f)\n", dept[i].name, dept[i].expenditure - dept[i].allocated);

}
}
}

///////main.c////

int main() {

int number;

Department dept[MAX_DEPARTMENTS];

printf("Enter number of departments: ");

scanf("%d", &number);

enterBudgets(dept, number);
calculateRemaining(dept, number);
displayBudgets(dept, number);
checkStatus(dept, number);

return 0;

}