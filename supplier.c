#include <stdio.h> 
#include <string.h>
#include "suppliers.h"

static int supplierIDs[MAX_SUPPLIERS];
static char supplierNames[MAX_SUPPLIERS][NAME_LEN];
static char supplierEmails[MAX_SUPPLIERS][EMAIL_LEN];
static char supplierPhones[MAX_SUPPLIERS][PHONE_LEN];
static char supplierTowns[MAX_SUPPLIERS][TOWN_LEN]; 

static int supplierCount = 0;

static void stripNewLine(char*s)
{
    s[strcspn(s,"\n")]='\0';
}

static void readNonEmpty(const char *prompt,char * buffer, int size)
{
    do{
        printf("%s",prompt);
        if(fgets(buffer,size,stdin)==NULL){
            buffer[0] ='\0';
        }
        stripNewline(buffer);
        if(strlen(buffer)==0) {
            printf(" Input can not be empty, Please try again.\n");
        }
    } while (strlen(buffer)==0);
}
/*==================================================================*/
/* addSupplier - capture one supplier record                        */
/*==================================================================*/
void addSupplier(void) 
{
    int id;
    char tempName[NAME_LEN]; 

    printf("/n---")
}