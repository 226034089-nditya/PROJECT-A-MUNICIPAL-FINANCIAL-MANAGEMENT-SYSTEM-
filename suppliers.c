/* Supplier Management module implementation */
#include <stdio.h>
#include <string.h>
#include "suppliers.h"

/* Module-private data                                      */
/* Parallel arrays: one slot per supplier across all fields.        */
static int  supplierIDs[MAX_SUPPLIERS];
static char supplierNames [MAX_SUPPLIERS][NAME_LEN];
static char supplierEmails[MAX_SUPPLIERS][EMAIL_LEN];
static char supplierPhones[MAX_SUPPLIERS][PHONE_LEN];
static char supplierTowns [MAX_SUPPLIERS][TOWN_LEN];

static int supplierCount = 0;   /* to show how many suppliers stored so far */

/* ---- strips the newline that fgets() keeps ------- */
static void stripNewline(char *s)
{
    s[strcspn(s, "\n")] = '\0';   
}

/* ---- reads a non-empty line into buffer ---------- */
static void readNonEmpty(const char *prompt, char *buffer, int size)
{
    do {
        printf("%s", prompt);
        if (fgets(buffer, size, stdin) == NULL) {
            buffer[0] = '\0';     /* treats the End Of File as empty */
        }
        stripNewline(buffer);
        if (strlen(buffer) == 0) {
            printf("  Input cannot be empty. Please try again.\n");
        }
    } while (strlen(buffer) == 0);
}

/* addSupplier - capture one supplier record                        */
void addSupplier(void)
{
    int  id;
    char tempName[NAME_LEN];

    printf("\n--- ADD SUPPLIER ---\n");

    /* Prevents overflow */
    if (supplierCount >= MAX_SUPPLIERS) {
        printf("Supplier list is full (%d max).\n", MAX_SUPPLIERS);
        return;
    }

    /* 1. Supplier ID - must be a positive number and unique */
    do {
        printf("Enter Supplier ID (positive integer): ");
        if (scanf("%d", &id) != 1) {           /* the user typed a non-numeric input */
            printf("  Invalid number. Try again.\n");
            while (getchar() != '\n');         /* flush the bad input */
            id = -1;                           /* force loop to repeat */
        } else {
            /* remove the enter key left behind*/
            getchar();                         
            if (id <= 0) {
                printf("  ID must be positive.\n");
            } else if (searchSupplierByID(id) >= 0) {
                printf("  ID %d already exists.\n", id);
                id = -1;
            }
        }
    } while (id <= 0);

    supplierIDs[supplierCount] = id;

    /* 2. Get supplier name - uses fgets() which allows space        */
    /*    scanf("%s") stops at a space; fgets() doesn't */
    readNonEmpty("Enter Supplier Name      : ",
                 supplierNames[supplierCount], NAME_LEN);

    /* 3. Get email - email must contain '@'        */
    do {
        readNonEmpty("Enter Supplier Email     : ",
                     supplierEmails[supplierCount], EMAIL_LEN);
        if (strchr(supplierEmails[supplierCount], '@') == NULL) {
            printf("  Email must contain '@'. Try again.\n");
        }
    } while (strchr(supplierEmails[supplierCount], '@') == NULL);

    /* 4. Phone is kept as a string because it may start with 0 or +  */
    readNonEmpty("Enter Supplier Phone     : ",
                 supplierPhones[supplierCount], PHONE_LEN);

    /* 5. Get town - fgets() to accept "Walvis Bay"                */
    readNonEmpty("Enter Supplier Town      : ",
                 supplierTowns[supplierCount], TOWN_LEN);

    supplierCount++;
    printf("Supplier added successfully. (%d stored)\n", supplierCount);

    /* strcpy() to copy the name into a backup)       */
    strcpy(tempName, supplierNames[supplierCount - 1]);
    printf("(Backup copy of name stored in tempName: \"%s\")\n", tempName);
}

/* ================================================================ */
/* displaySuppliers - print every stored supplier                   */
/* ================================================================ */
void displaySuppliers(void)
{
    int i;

    printf("\n--- SUPPLIER LIST (%d) ---\n", supplierCount);

    if (supplierCount == 0) {
        printf("No suppliers recorded yet.\n");
        return;
    }

    printf("%-6s %-25s %-25s %-15s %-15s\n",
           "ID", "Name", "Email", "Phone", "Town");
    printf("-------------------------------------------------------------------------------\n");
/* print a row per supplier */
    for (i = 0; i < supplierCount; i++) {
        printf("%-6d %-25s %-25s %-15s %-15s\n",
               supplierIDs[i],
               supplierNames[i],
               supplierEmails[i],
               supplierPhones[i],
               supplierTowns[i]);
    }
}

/* ================================================================ */
/* searchSupplier - find name using strcmp()                        */
/* ================================================================ */
void searchSupplier(void)
{
    int  i, found = 0;
    char target[NAME_LEN];

    if (supplierCount == 0) {
        printf("No suppliers to search.\n");
        return;
    }

    readNonEmpty("\nEnter supplier name to search: ", target, NAME_LEN);

    for (i = 0; i < supplierCount; i++) {
        /* strcmp() is used to compare strings. Returns 0 when strings are the same */
        if (strcmp(supplierNames[i], target) == 0) {
            printf("\nSupplier found at position %d:\n", i);
            printf("  ID    : %d\n",  supplierIDs[i]);
            printf("  Name  : %s\n",  supplierNames[i]);
            printf("  Email : %s\n",  supplierEmails[i]);
            printf("  Phone : %s\n",  supplierPhones[i]);
            printf("  Town  : %s\n",  supplierTowns[i]);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Supplier \"%s\" not found.\n", target);
    }
}

/* ================================================================ */
/* getSupplierCount            */
/* ================================================================ */
int getSupplierCount(void)
{
    return supplierCount;
}

/* ================================================================ */
/* searchSupplierByID - private helper used inside this file only.              */
/* Returns index or -1 if not found                                           */
/* ================================================================ */
int searchSupplierByID(int id)
{
    int i;
    for (i = 0; i < supplierCount; i++) {
        if (supplierIDs[i] == id) {
            return i;
        }
    }
    return -1;
}