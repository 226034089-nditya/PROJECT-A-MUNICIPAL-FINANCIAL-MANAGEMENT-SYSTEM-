/* assets.c - Asset Management module (basic asset register) */

#include <stdio.h>
#include <string.h>
#include "assets.h"
#include "input.h"

char assetTypes[NUMBER_OF_TYPES][TEXT_SIZE] = {"Vehicle", "Computer", "Building", "Equipment", "Office Furniture"};
char conditions[3][10] = {"Good", "Fair", "Poor"};

char assetId[MAX_ASSETS][10];
char assetName[MAX_ASSETS][TEXT_SIZE];
int assetType[MAX_ASSETS];        /* index into assetTypes[] */
double assetValue[MAX_ASSETS];
char assetDepartment[MAX_ASSETS][TEXT_SIZE];
int assetCondition[MAX_ASSETS];   /* index into conditions[] */
int assetCount = 0;

void assetMenu(void)
{
    int choice;

    do
    {
        printf("\n========== ASSET MANAGEMENT ==========\n");
        printf("1. Add asset\n");
        printf("2. Display all assets\n");
        printf("3. Search for an asset\n");
        printf("4. Back to main menu\n");
        choice = readInt("Enter your choice: ", 1, 4);

        switch (choice)
        {
            case 1:
                addAsset();
                break;
            case 2:
                displayAssets();
                break;
            case 3:
                searchAsset();
                break;
            case 4:
                printf("Returning to main menu...\n");
                break;
        }
    } while (choice != 4);
}

void addAsset(void)
{
    char id[10];
    int i;

    if (assetCount >= MAX_ASSETS)
    {
        printf("Sorry, the asset register is full.\n");
        return;
    }

    printf("\n--- Add New Asset ---\n");

    readString("Asset ID (e.g. A001): ", id, 10);
    while (findAssetById(id) != -1)
    {
        printf("  Error: asset ID %s already exists.\n", id);
        readString("Asset ID (e.g. A001): ", id, 10);
    }
    strcpy(assetId[assetCount], id);

    readString("Asset name: ", assetName[assetCount], TEXT_SIZE);

    printf("Asset type:\n");
    for (i = 0; i < NUMBER_OF_TYPES; i++)
    {
        printf("  %d. %s\n", i + 1, assetTypes[i]);
    }
    assetType[assetCount] = readInt("Choose type: ", 1, NUMBER_OF_TYPES) - 1;

    assetValue[assetCount] = readMoney("Purchase value (N$): ");
    readString("Department: ", assetDepartment[assetCount], TEXT_SIZE);

    printf("Condition:\n");
    for (i = 0; i < 3; i++)
    {
        printf("  %d. %s\n", i + 1, conditions[i]);
    }
    assetCondition[assetCount] = readInt("Choose condition: ", 1, 3) - 1;

    assetCount++;
    printf("Asset added successfully. Total assets: %d\n", assetCount);
}

void displayAssets(void)
{
    int i;

    if (assetCount == 0)
    {
        printf("No assets have been added yet.\n");
        return;
    }

    printf("\n%-6s %-22s %-17s %14s %-16s %s\n", "ID", "Name", "Type", "Value (N$)", "Department", "Condition");
    printLine();
    for (i = 0; i < assetCount; i++)
    {
        printf("%-6s %-22s %-17s %14.2f %-16s %s\n", assetId[i], assetName[i], assetTypes[assetType[i]],
               assetValue[i], assetDepartment[i], conditions[assetCondition[i]]);
    }
    printLine();
    printf("Total assets: %d\n", assetCount);
}

void displayOneAsset(int index)
{
    printf("\nAsset ID       : %s\n", assetId[index]);
    printf("Name           : %s\n", assetName[index]);
    printf("Type           : %s\n", assetTypes[assetType[index]]);
    printf("Purchase value : N$%.2f\n", assetValue[index]);
    printf("Department     : %s\n", assetDepartment[index]);
    printf("Condition      : %s\n", conditions[assetCondition[index]]);
}

void searchAsset(void)
{
    int choice;
    int i;
    int index;
    int type;
    int found = 0;
    char searchText[TEXT_SIZE];

    if (assetCount == 0)
    {
        printf("No assets have been added yet.\n");
        return;
    }

    printf("\nSearch by:\n");
    printf("1. Asset ID\n");
    printf("2. Name\n");
    printf("3. Type\n");
    printf("4. Department\n");
    choice = readInt("Enter your choice: ", 1, 4);

    if (choice == 1)
    {
        readString("Enter asset ID: ", searchText, TEXT_SIZE);
        index = findAssetById(searchText);
        if (index == -1)
        {
            printf("No asset found with ID %s.\n", searchText);
        }
        else
        {
            displayOneAsset(index);
        }
        return;
    }

    if (choice == 3)
    {
        for (i = 0; i < NUMBER_OF_TYPES; i++)
        {
            printf("  %d. %s\n", i + 1, assetTypes[i]);
        }
        type = readInt("Choose type: ", 1, NUMBER_OF_TYPES) - 1;

        for (i = 0; i < assetCount; i++)
        {
            if (assetType[i] == type)
            {
                displayOneAsset(i);
                found++;
            }
        }
    }
    else
    {
        readString("Enter text to search for: ", searchText, TEXT_SIZE);

        for (i = 0; i < assetCount; i++)
        {
            if ((choice == 2 && containsText(assetName[i], searchText)) ||
                (choice == 4 && containsText(assetDepartment[i], searchText)))
            {
                displayOneAsset(i);
                found++;
            }
        }
    }

    if (found == 0)
    {
        printf("No matching assets found.\n");
    }
    else
    {
        printf("\n%d asset(s) found.\n", found);
    }
}

int findAssetById(char id[])
{
    int i;

    for (i = 0; i < assetCount; i++)
    {
        if (sameText(assetId[i], id))
        {
            return i;
        }
    }
    return -1;
}

int getAssetCount(void)
{
    return assetCount;
}

double getAssetValue(int index)
{
    return assetValue[index];
}

int getAssetTypeNumber(int index)
{
    return assetType[index];
}

void getAssetTypeName(int typeNumber, char name[])
{
    strcpy(name, assetTypes[typeNumber]);
}
