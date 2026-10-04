/* input.h - helper functions for reading and checking user input */

#ifndef INPUT_H
#define INPUT_H

#define TEXT_SIZE 50

void readString(char prompt[], char text[], int size);
int readInt(char prompt[], int min, int max);
double readMoney(char prompt[]);
void toLowerCase(char source[], char result[]);
int containsText(char text[], char searchText[]);
int sameText(char first[], char second[]);
void pressEnter(void);
void printLine(void);

#endif
