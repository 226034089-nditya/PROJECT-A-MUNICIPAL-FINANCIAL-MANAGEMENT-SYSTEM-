/* input.c - helper functions for reading and checking user input
   All modules use these so that input is validated the same way everywhere. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "input.h"

/* reads one line from the keyboard into line[]
   if the user typed more than fits, the rest of the line is thrown away */
void readLine(char line[], int size)
{
    int length;
    int c;

    if (fgets(line, size, stdin) == NULL)
    {
        /* no more input (for example when input comes from a file) */
        printf("\nNo more input. Closing the program.\n");
        exit(0);
    }

    length = strlen(line);

    if (length > 0 && line[length - 1] == '\n')
    {
        line[length - 1] = '\0';
    }
    else
    {
        /* line was too long, clear the rest of it */
        c = getchar();
        while (c != '\n' && c != EOF)
        {
            c = getchar();
        }
    }
}

/* removes spaces at the start and end of a string */
void trimSpaces(char text[])
{
    int start = 0;
    int end;
    int i;

    while (text[start] == ' ' || text[start] == '\t')
    {
        start++;
    }

    /* move everything to the left */
    i = 0;
    while (text[start + i] != '\0')
    {
        text[i] = text[start + i];
        i++;
    }
    text[i] = '\0';

    end = strlen(text) - 1;
    while (end >= 0 && (text[end] == ' ' || text[end] == '\t'))
    {
        text[end] = '\0';
        end--;
    }
}

/* asks for text and keeps asking until something that is not empty is typed */
void readString(char prompt[], char text[], int size)
{
    char line[200];

    while (1)
    {
        printf("%s", prompt);
        readLine(line, 200);
        trimSpaces(line);

        if (strlen(line) == 0)
        {
            printf("  Error: this field cannot be empty. Please try again.\n");
        }
        else if ((int)strlen(line) >= size)
        {
            printf("  Error: too long. Maximum is %d characters.\n", size - 1);
        }
        else
        {
            strcpy(text, line);
            return;
        }
    }
}

/* asks for a whole number between min and max */
int readInt(char prompt[], int min, int max)
{
    char line[100];
    int number;
    char extra;

    while (1)
    {
        printf("%s", prompt);
        readLine(line, 100);

        /* sscanf returns 1 only if there is a number and nothing else after it */
        if (sscanf(line, "%d %c", &number, &extra) != 1)
        {
            printf("  Error: please enter a whole number.\n");
        }
        else if (number < min || number > max)
        {
            printf("  Error: invalid choice. Enter a number from %d to %d.\n", min, max);
        }
        else
        {
            return number;
        }
    }
}

/* asks for an amount of money, it may not be negative */
double readMoney(char prompt[])
{
    char line[100];
    double amount;
    char extra;

    while (1)
    {
        printf("%s", prompt);
        readLine(line, 100);

        if (sscanf(line, "%lf %c", &amount, &extra) != 1)
        {
            printf("  Error: please enter a valid number (for example 15000 or 15000.50).\n");
        }
        else if (amount < 0)
        {
            printf("  Error: amount cannot be negative.\n");
        }
        else if (amount > 1000000000)
        {
            printf("  Error: amount is too large.\n");
        }
        else
        {
            return amount;
        }
    }
}

/* copies source into result with all letters changed to small letters */
void toLowerCase(char source[], char result[])
{
    int i = 0;

    while (source[i] != '\0')
    {
        result[i] = tolower((unsigned char)source[i]);
        i++;
    }
    result[i] = '\0';
}

/* returns 1 if searchText is found inside text (ignores capital letters) */
int containsText(char text[], char searchText[])
{
    char lowerText[200];
    char lowerSearch[200];

    toLowerCase(text, lowerText);
    toLowerCase(searchText, lowerSearch);

    if (strstr(lowerText, lowerSearch) != NULL)
    {
        return 1;
    }
    return 0;
}

/* returns 1 if the two strings are the same (ignores capital letters) */
int sameText(char first[], char second[])
{
    char lowerFirst[200];
    char lowerSecond[200];

    toLowerCase(first, lowerFirst);
    toLowerCase(second, lowerSecond);

    if (strcmp(lowerFirst, lowerSecond) == 0)
    {
        return 1;
    }
    return 0;
}

void pressEnter(void)
{
    char line[100];

    printf("\nPress Enter to continue...");
    readLine(line, 100);
}

void printLine(void)
{
    printf("--------------------------------------------------------------------------------\n");
}
