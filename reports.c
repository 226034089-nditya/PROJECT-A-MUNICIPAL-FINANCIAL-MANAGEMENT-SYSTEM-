#include <stdio.h>

struct Employee { char name[50]; double baseSalary; double bonus; };
struct Budget { char department[50]; double allocated; double expenditure; };
struct Supplier { char supplierName[50]; char category[50]; };
struct Asset { char assetName[50]; int quantity; };

void employeeReport(struct Employee e[], int c){
    double total=0, h=e[0].baseSalary+e[0].bonus, l=e[0].baseSalary+e[0].bonus;
    printf("\n===== EMPLOYEE REPORT =====\n");
    for(int i=0;i<c;i++){ double ts=e[i].baseSalary+e[i].bonus; printf("%s - N$ %.2f\n",e[i].name,ts); total+=ts; if(ts>h)h=ts; if(ts<l)l=ts; }
    printf("Total: N$ %.2f\nAvg: N$ %.2f\nHighest: N$ %.2f\nLowest: N$ %.2f\n",total,total/c,h,l);
}
void budgetReport(struct Budget b[], int c){
    double a=0,ex=0; int exc=0;
    for(int i=0;i<c;i++){ a+=b[i].allocated; ex+=b[i].expenditure; if(b[i].allocated-b[i].expenditure<0)exc++; }
    printf("\n===== BUDGET REPORT =====\nAllocated: %.2f\nExpenditure: %.2f\nRemaining: %.2f\nExceeded: %d\n",a,ex,a-ex,exc);
}
void supplierReport(struct Supplier s[], int c){
    printf("\n===== SUPPLIER REPORT =====\n");
    for(int i=0;i<c;i++) printf("%d. %s - %s\n",i+1,s[i].supplierName,s[i].category);
}
void assetReport(struct Asset as[], int c){
    printf("\n===== ASSET REPORT =====\n");
    for(int i=0;i<c;i++) printf("%d. %s - %d units\n",i+1,as[i].assetName,as[i].quantity);
}
int main(){
    struct Employee employees[3] = {{"Alice",15000,2000},{"Bob",12000,1500},{"Charlie",18000,2500}};
    struct Budget budgets[2] = {{"IT",50000,45000},{"HR",20000,22000}};
    struct Supplier suppliers[2] = {{"Supplier A","Tech Supplies"},{"Supplier B","Office Furniture"}};
    struct Asset assets[2] = {{"Laptops",15},{"Desks",30}};
    int choice;
    do{
        printf("\n--- Reports Menu ---\n1. Employee\n2. Budget\n3. Supplier\n4. Asset\n5. Exit\nChoice: ");
        scanf("%d",&choice);
        if(choice==1) employeeReport(employees,3);
        else if(choice==2) budgetReport(budgets,2);
        else if(choice==3) supplierReport(suppliers,2);
        else if(choice==4) assetReport(assets,2);
    }while(choice!=5);
    return 0;
}
