//==========================================
// Name: BattleShipCPE223
// Author: Wyatt Bowman
// Date: 12/10/25
// Version: V1.2
// Description: Comments
// Changes: Added Comments
//
//==========================================

#include <stdio.h>
#include <string.h> // Required to use strings
#include <stdlib.h> // Required for system()
#include <stdbool.h>
#include "functions.h"
int size;
int playerPoints[2] = {0};
int CHECK[2][15][15] = {0};


int main(){
    // Start Variables
    gameStart:
    int userX, userY, rotate, turn = 0, booleanTurn = 0, value = 1;
    // declaring one dimensional integers
    int boatLength[5] = {5, 4, 3, 3, 2};
    // Boat length array
    int shipValueType[5] = {2,4,6,8,10};
    int playerData[2][15][15]={0}; // player, row, column
    // This stores all the player data for each player

    char playerName[2][31];
    char shipValueAbrv[14][5] = {" ~~ ","Miss"," AC ","XACX"," BA ","XBAX"," SU ","XSUX"," CR ","XCRX"," DE ","XDEX"," [] ","Sunk"};
    // this stores the string values for the display
    char mainScreenOption = 0;
    char oldMainScreenOption = 0;

    char ships[5][20] = {"Carrier", "Battleship", "Submarine", "Cruiser", "Destroyer"};
    // for printing ships on the display

    bool screenShake = false;
    bool airStrikeMode = false;
    //End Variables

    while(!(mainScreenOption == 'q' || mainScreenOption == 'Q')){
    // Confirm
        battleShipCover_ASCII(); // ASCII ART from void function
        startScreen(value);
        while(!validateUserInput(&mainScreenOption)){ // running validation check for user input
            printf("Invalid Input");
        }

        if(mainScreenOption == 'w' || mainScreenOption == 'W')
        // UP
            value--;
                if(value < 1)
                    value = 3;
        else if (mainScreenOption == 's' || mainScreenOption == 'S')
        // DOWN
            value++;
                if(value > 3)
                    value = 1;
        system("cls");
        // clears terminal
    }

    switch(value){
        case 1: // PLAY GAME
            for(int playerNumber = 0; playerNumber < 2; playerNumber++){ // getting the usernames of each player
                printf("\t\t\n\nWhat is the name of Player %d?(MAX 30 CHAR):\t\n\n", playerNumber + 1);
                fgets(playerName[playerNumber], sizeof(playerName[playerNumber]), stdin);
                int length = strlen(playerName[playerNumber]); // bad practice fix later
                if (length > 0 && playerName[playerNumber][length - 1] == '\n') {
                    playerName[playerNumber][length - 1] = '\0'; // strip newline
                } else {
                // flush leftovers
                    int ch; // burner variable
                    while ((ch = getchar()) != '\n' && ch != EOF);
                    // checking its not the new line and thats its not the end of file
                    // this is for clearing buffer
                }
            }
            // Get Usernames
            getSize(&size);
            //Player One Placement
            getMode(&airStrikeMode);
            // does the user want to play airstrike mode?
            getUserBoatPlacement(playerData, playerName, booleanTurn, boatLength, shipValueType, shipValueAbrv, ships);
            //Transition
            transistion(turn + 1);
            //Player Two Placement
            getUserBoatPlacement(playerData, playerName, booleanTurn + 1, boatLength, shipValueType, shipValueAbrv, ships);
            //Transition
            transistion(turn);

            while(1){ // need win condition
                if(screenShake == true){
                    for(int shakeAmount = 0; shakeAmount < 6; shakeAmount++){
                        displayBoard(playerName, (!(shakeAmount % 2)), booleanTurn, playerData, shipValueAbrv);
                        _sleep(300); //sleep 100ms from windows.h
                    }
                screenShake = false;
                }
                // Screenshake code
                displayBoard(playerName, 0, booleanTurn, playerData, shipValueAbrv); // just testing output
                // Display The board
                attackSmack(booleanTurn, playerData, playerName, shipValueAbrv, &screenShake, airStrikeMode);
                // Attack Code
                printf("\n\t\t Points: %d", playerPoints[booleanTurn]);
                winCondition(playerData, booleanTurn);
                if(playerPoints[booleanTurn] >= 11200){
                    winScreen_ASCII(booleanTurn);
                    return 0;
                }
                // Test Win Condition
                turn++;
                //next persons turn
                booleanTurn = turn % 2;
                // for switching back and forth
                transistion(booleanTurn);
                //in between slide
            }
        break;
        case 2: // HELP OPTION
            printf("\n\nVisit \"https://www.wikihow.com/Play-Battleship\" for more information\n\n");
            // HELP FOR USER
            printf("\n\n Press Enter to Go Back To Main Page");
            getc(stdin);
            system("cls");
            goto gameStart;

        break;
        case 3: // CREDITS
            printf("\n\nDeveloped by Wyatt Bowman and Kieran Cavanagh\n\n");
            titleScreen();
            printf("\n\n Press Enter to Go Back To Main Page");
            getc(stdin);
            system("cls");
            goto gameStart;
        break;
        default:
            printf("Invalid Input, Try again");
    }
    return 0;
}

// END MAIN
