/* suppliers.c - Supplier Management module */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "suppliers.h"
#include "input.h"

char supId[MAX_SUPPLIERS][10];
char supName[MAX_SUPPLIERS][TEXT_SIZE];
char supEmail[MAX_SUPPLIERS][TEXT_SIZE];
char supPhone[MAX_SUPPLIERS][20];
char supTown[MAX_SUPPLIERS][TEXT_SIZE];
char supService[MAX_SUPPLIERS][TEXT_SIZE];
int supplierCount = 0;

void supplierMenu(void)
{
    int choice;

    do
    {
        printf("\n========== SUPPLIER MANAGEMENT ==========\n");
        printf("1. Add supplier\n");
        printf("2. Display all suppliers\n");
        printf("3. Search for a supplier\n");
        printf("4. Compare two suppliers\n");
        printf("5. Back to main menu\n");
        choice = readInt("Enter your choice: ", 1, 5);

        switch (choice)
        {
            case 1:
                addSupplier();
                break;
            case 2:
                displaySuppliers();
                break;
            case 3:
                searchSupplier();
                break;
            case 4:
                compareSuppliers();
                break;
            case 5:
                printf("Returning to main menu...\n");
                break;
        }
    } while (choice != 5);
}

void addSupplier(void)
{
    char id[10];

    if (supplierCount >= MAX_SUPPLIERS)
    {
        printf("Sorry, the supplier list is full.\n");
        return;
    }

    printf("\n--- Add New Supplier ---\n");

    readString("Supplier ID (e.g. S001): ", id, 10);
    while (findSupplierById(id) != -1)
    {
        printf("  Error: supplier ID %s already exists.\n", id);
        readString("Supplier ID (e.g. S001): ", id, 10);
    }
    strcpy(supId[supplierCount], id);

    readString("Supplier name: ", supName[supplierCount], TEXT_SIZE);

    readString("Email: ", supEmail[supplierCount], TEXT_SIZE);
    while (!isValidEmail(supEmail[supplierCount]))
    {
        printf("  Error: email must look like name@company.com\n");
        readString("Email: ", supEmail[supplierCount], TEXT_SIZE);
    }

    readString("Telephone number: ", supPhone[supplierCount], 20);
    while (!isValidPhone(supPhone[supplierCount]))
    {
        printf("  Error: telephone must have 7 to 15 digits (a + at the start is allowed).\n");
        readString("Telephone number: ", supPhone[supplierCount], 20);
    }

    readString("Town/Location: ", supTown[supplierCount], TEXT_SIZE);
    readString("Goods/Service supplied: ", supService[supplierCount], TEXT_SIZE);

    supplierCount++;
    printf("Supplier added successfully. Total suppliers: %d\n", supplierCount);
}

void displaySuppliers(void)
{
    int i;

    if (supplierCount == 0)
    {
        printf("No suppliers have been added yet.\n");
        return;
    }

    printf("\n%-6s %-22s %-24s %-14s %-12s %s\n", "ID", "Name", "Email", "Telephone", "Town", "Service");
    printLine();
    for (i = 0; i < supplierCount; i++)
    {
        printf("%-6s %-22s %-24s %-14s %-12s %s\n", supId[i], supName[i], supEmail[i],
               supPhone[i], supTown[i], supService[i]);
    }
    printLine();
    printf("Total suppliers: %d\n", supplierCount);
}

void displayOneSupplier(int index)
{
    printf("\nSupplier ID : %s\n", supId[index]);
    printf("Name        : %s\n", supName[index]);
    printf("Email       : %s\n", supEmail[index]);
    printf("Telephone   : %s\n", supPhone[index]);
    printf("Town        : %s\n", supTown[index]);
    printf("Service     : %s\n", supService[index]);
}

void searchSupplier(void)
{
    int choice;
    int i;
    int index;
    int found = 0;
    int match;
    char searchText[TEXT_SIZE];

    if (supplierCount == 0)
    {
        printf("No suppliers have been added yet.\n");
        return;
    }

    printf("\nSearch by:\n");
    printf("1. Supplier ID\n");
    printf("2. Name\n");
    printf("3. Town/Location\n");
    printf("4. Goods/Service\n");
    choice = readInt("Enter your choice: ", 1, 4);

    if (choice == 1)
    {
        readString("Enter supplier ID: ", searchText, TEXT_SIZE);
        index = findSupplierById(searchText);
        if (index == -1)
        {
            printf("No supplier found with ID %s.\n", searchText);
        }
        else
        {
            displayOneSupplier(index);
        }
        return;
    }

    readString("Enter text to search for: ", searchText, TEXT_SIZE);

    for (i = 0; i < supplierCount; i++)
    {
        match = 0;
        switch (choice)
        {
            case 2:
                match = containsText(supName[i], searchText);
                break;
            case 3:
                match = containsText(supTown[i], searchText);
                break;
            case 4:
                match = containsText(supService[i], searchText);
                break;
        }

        if (match)
        {
            displayOneSupplier(i);
            found++;
        }
    }

    if (found == 0)
    {
        printf("No suppliers matched \"%s\".\n", searchText);
    }
    else
    {
        printf("\n%d supplier(s) found.\n", found);
    }
}

/* shows two suppliers next to each other and says what they have in common */
void compareSuppliers(void)
{
    char id1[10];
    char id2[10];
    int first;
    int second;

    if (supplierCount < 2)
    {
        printf("You need at least 2 suppliers to compare.\n");
        return;
    }

    readString("Enter first supplier ID: ", id1, 10);
    first = findSupplierById(id1);
    if (first == -1)
    {
        printf("No supplier found with ID %s.\n", id1);
        return;
    }

    readString("Enter second supplier ID: ", id2, 10);
    second = findSupplierById(id2);
    if (second == -1)
    {
        printf("No supplier found with ID %s.\n", id2);
        return;
    }

    if (first == second)
    {
        printf("You entered the same supplier twice.\n");
        return;
    }

    printf("\n%-12s %-25s %-25s\n", "", supId[first], supId[second]);
    printLine();
    printf("%-12s %-25s %-25s\n", "Name", supName[first], supName[second]);
    printf("%-12s %-25s %-25s\n", "Email", supEmail[first], supEmail[second]);
    printf("%-12s %-25s %-25s\n", "Telephone", supPhone[first], supPhone[second]);
    printf("%-12s %-25s %-25s\n", "Town", supTown[first], supTown[second]);
    printf("%-12s %-25s %-25s\n", "Service", supService[first], supService[second]);
    printLine();

    if (sameText(supTown[first], supTown[second]))
    {
        printf("Both suppliers are in %s.\n", supTown[first]);
    }
    else
    {
        printf("The suppliers are in different towns.\n");
    }

    if (sameText(supService[first], supService[second]))
    {
        printf("Both suppliers supply the same goods/service: %s.\n", supService[first]);
    }
    else
    {
        printf("The suppliers supply different goods/services.\n");
    }
}

int findSupplierById(char id[])
{
    int i;

    for (i = 0; i < supplierCount; i++)
    {
        if (sameText(supId[i], id))
        {
            return i;
        }
    }
    return -1;
}

/* simple email check: one @, something before it, and a dot after it */
int isValidEmail(char email[])
{
    int i;
    int atPosition = -1;
    int atCount = 0;
    int dotAfterAt = 0;
    int length = strlen(email);

    for (i = 0; i < length; i++)
    {
        if (email[i] == ' ')
        {
            return 0;
        }
        if (email[i] == '@')
        {
            atCount++;
            atPosition = i;
        }
    }

    if (atCount != 1 || atPosition == 0)
    {
        return 0;
    }

    /* there must be a dot after the @ but not right after it and not at the end */
    for (i = atPosition + 2; i < length - 1; i++)
    {
        if (email[i] == '.')
        {
            dotAfterAt = 1;
        }
    }

    return dotAfterAt;
}

/* phone may only have digits (and a + at the start), 7 to 15 digits */
int isValidPhone(char phone[])
{
    int i;
    int digits = 0;
    int length = strlen(phone);

    for (i = 0; i < length; i++)
    {
        if (isdigit((unsigned char)phone[i]))
        {
            digits++;
        }
        else if (!(i == 0 && phone[i] == '+'))
        {
            return 0;
        }
    }

    if (digits >= 7 && digits <= 15)
    {
        return 1;
    }
    return 0;
}

int getSupplierCount(void)
{
    return supplierCount;
}
