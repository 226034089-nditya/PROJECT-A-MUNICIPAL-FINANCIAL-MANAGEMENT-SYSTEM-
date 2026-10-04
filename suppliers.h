/* suppliers.h - Supplier Management module */

#ifndef SUPPLIERS_H
#define SUPPLIERS_H

#define MAX_SUPPLIERS 50

void supplierMenu(void);
void addSupplier(void);
void displaySuppliers(void);
void searchSupplier(void);
void compareSuppliers(void);
void displayOneSupplier(int index);

int findSupplierById(char id[]);
int isValidEmail(char email[]);
int isValidPhone(char phone[]);

int getSupplierCount(void);

#endif
