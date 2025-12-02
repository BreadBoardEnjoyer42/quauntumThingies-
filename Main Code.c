//==========================================
// Name: BattleShipCPE223
// Author: Wyatt Bowman
// Date: 11/29/25
// Version: V0.7
// Description: Currently just first three features
// Changes: everything is split up into header funcitons and other functions
//==========================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Required to use strings
#include <stdlib.h> // Required for system()
#include <stdbool.h>
#include "functions.h"
#include "ASCIIfunctions.h"


int main(){
    //Start Variables
    int userX, userY, rotate, turn = 0, booleanTurn = 0, value = 1;
    int boatLength[5] = {5, 4, 3, 3, 2};

    char playerData[2][10][10][3]; // player, row, column, max size of char
    char Ships[5][20] = {"Carrier", "Battleship", "Submarine", "Cruiser", "Destroyer"}; // names and such
    char playerName[2][100]; // make smaller in future
    char boardPieces[5][3] = {"AC","BA","CR","SU","DE"};
    char mainScreenOption = 0;
    char oldMainScreenOption = 0;

    bool screenShake = 1; // FOR GAME NEEDS TO BE DYNAMIC
    //End Variables

    while(1){ // change to when user enters new line then quits
        battleShipCover_ASCII(); // ASCII ART from void function
        startScreen(value);
        while(validateUserInput(&mainScreenOption) != 1){ // running validation check for user input
            printf("Invalid Input");
        }

        if(mainScreenOption == 'w' || mainScreenOption == 'W')
            value--;
                if(value < 1)
                    value = 3;
        else if (mainScreenOption == 's' || mainScreenOption == 'S')
            value++;
                if(value > 3)
                    value = 1;
        else if (mainScreenOption == 'q' || mainScreenOption == 'Q'){
            system("cls");
            break;
        }

        system("cls"); // clears terminal
    }

    switch(value){

        case 1: // PLAY GAME

            for(int playerNumber = 0; playerNumber < 2; playerNumber++){ // getting the usernames of each player
                printf("\t\t\n\nWhat is the name of Player %d?:\t\n\n", playerNumber + 1);
                fgets(playerName[playerNumber], sizeof(playerName[playerNumber]), stdin);
                int length = strlen(playerName[playerNumber]); // bad practice fix later
                playerName[playerNumber][length - 1] = '\0'; // making sure the last real character isn't a newline
            }

            for (int p = 0; p < 2; p++) {
                for (int i = 0; i < 10; i++) {
                    for (int j = 0; j < 10; j++) {
                        strcpy(playerData[p][i][j], "  ");
                        //strcpy(fogPlayerData[p][i][j], "  ");
                    }
                }
            }
            for(int g = 0; g < 2; g++){
                getUserBoatPlacement(playerData, boardPieces, playerName, g, boatLength);
            }

            while(1){ // need win condition

                displayBoard(playerName, screenShake, booleanTurn, playerData); // just testing output

                if(screenShake){
                    for(int shakeAmount = 0; shakeAmount < 4; shakeAmount++){
                        displayBoard(playerName, shakeAmount % 2 == 0, booleanTurn, playerData);
                        _sleep(500); //sleep 100ms from windows.h
                    }
                }

                scanf("%d");
                turn++;
                booleanTurn = turn % 2;

            }
        break;
        case 2: // HELP OPTION
            printf("\n\nVisit \"https://www.wikihow.com/Play-Battleship\" for more information\n\n");
        break;
        case 3: // CREDITS
            printf("\n\nDeveloped by Wyatt Bowman and Kieran Cavanagh\n\n");
        break;

        default:
            printf("Invalid Input, Try again");
    }


    return 0;

}

// END MAIN


