#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED
#include <stdbool.h>


// MAIN LOGIC FUNCTIONS
int startScreen(int);

int validateUserInput(char *out);

void pause(char player[2][100]);

void displayBoard(char player[2][100], bool screenShake, int booleanTurn, int playerInput[2][10][10], char shipValueAbrv[14][5]);

void printPlayerBoardRow(int player,int row,int playerInput[2][10][10],char shipValueAbrv[14][5]);

void printPlayerFogBoardRow(int player,int row,int playerInput[2][10][10],char shipValueAbrv[14][5]);

void getUserBoatPlacement(int playerData[2][10][10], char playerName[2][100], int turn, int boatLength[5],
                          int shipValueType[5], char shipValueAbrv[14][5], char ships[5][20]);
void transistion(int);

void attackSmack(int turn, int playerData[2][10][10], char playerName[2][100], char shipValueAbrv[14][5]);
// ASCII CODE FUNCTIONS
void winScreen_ASCII(int booleanTurn);

void battleShipCover_ASCII();

void battleShipPause_ASCII();

void inbetweenScreen();

void titleScreen();

#endif // FUNCTIONS_H_INCLUDED
