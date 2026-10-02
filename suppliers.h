#ifndef SUPPLIERS_H
#define SUPPLIERS_H 

#define MAX_SUPPLIERS 50 
#define NAME_LEN 50
#define EMAIL_LEN 50 
#define PHONE_LEN 20
#define TOWN_LEN 50 

void addSupplier(void);
void displaySuppliers(void);
void searchSupplier(void);
int getSupplierCount(void); 
int searchSupplierByID(int id);

#endif 
