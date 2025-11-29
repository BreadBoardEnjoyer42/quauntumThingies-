//==========================================
// Name: BattleShipCPE223
// Author: Wyatt Bowman
// Date: 11/29/25
// Version: V0.6
// Description: ASCII code yay
// Changes: Added basic ascii code functions for win condition, maybe add some more art later.
//          Also added a prototype for a pause function, need more features before I can test.
//==========================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Required to use strings
#include <stdlib.h> // Required for system()
#include <stdbool.h>


int startScreen(int);
void battleShipCover_ASCII();
void battleShipPause_ASCII();
void pause(char player[2][100]);
void winScreen_ASCII(int booleanTurn);
void displayBoard(char player[2][100], bool, int, char playerInput[2][10][10][3], char fogPlayerData[2][10][10][3]);
void getUserBoatPlacement(char playerData[2][10][10][3], char fogPlayerData[2][10][10][3], char boardPieces[5][3],
                          char playerName[2][100], int, int boatLength[5]);

int main()
{
    //Start Variables
    int userX, userY, mainScreenOption = -1, oldMainScreenOption, rotate, turn = 0, booleanTurn = 0;
    int boatLength[5] = {5, 4, 3, 3, 2};

    char playerData[2][10][10][3]; // player, row, column, max size of char
    char fogPlayerData[2][10][10][3]; // player, row, column, max size of char
    char Ships[5][20] = {"Carrier", "Battleship", "Submarine", "Cruiser", "Destroyer"}; // names and such
    char playerName[2][100]; // make smaller in future
    char boardPieces[5][3] = {"AC","BA","CR","SU","DE"};


    bool screenShake = 0; // FOR GAME NEEDS TO BE DYNAMIC
    //End Variables

    while(mainScreenOption != 0){ // change to when user enters new line then quits
        battleShipCover_ASCII(); // ASCII ART from void function
        startScreen(mainScreenOption);
        oldMainScreenOption = mainScreenOption;
        scanf("%d", &mainScreenOption); // user input for the options
        system("cls"); // clears terminal
    }

    switch(oldMainScreenOption){

        case 1: // PLAY GAME
            scanf("%*[^\n]");  // Skip characters until newline
            scanf("%*c");      // Consume the newline

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
                        strcpy(fogPlayerData[p][i][j], "  ");
                    }
                }
            }
            for(int g = 0; g < 2; g++){
                getUserBoatPlacement(playerData, fogPlayerData, boardPieces, playerName, g, boatLength);
            }


            while(1){ // need win condition

                displayBoard(playerName, screenShake, booleanTurn, playerData, fogPlayerData); // just testing output

                if(screenShake){
                    for(int shakeAmount = 0; shakeAmount < 4; shakeAmount++){
                        displayBoard(playerName, shakeAmount % 2 == 0, booleanTurn, playerData, fogPlayerData);
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









// START USER DEFINED FUNCTIONS

// Function to print the selection screen

int startScreen(int option){ // main screen code, helps select and change user input
    printf("\n\n\n\t\t\t   Pick an option (1-3)\n\n");

    if(option == 1) // option 1
        printf("\t\t\t     >>>Play Game!<<<\n\n");
    else
        printf("\t\t\t\tPlay Game!\n\n");

    if(option == 2) // option 2
        printf("\t\t\t     >>>Help<<<\n\n");
    else
        printf("\t\t\t\tHelp\n\n");

    if(option == 3) // option 3
        printf("\t\t\t     >>>Credits<<<\n\n");
    else
        printf("\t\t\t\tCredits\n\n");

    printf("\t\t\t  Press \"0\" When Selected\n");

    return 1;
}

// Void Functions

// Function to display the board with improved GUI

void displayBoard(char player[2][100], bool screenShake, int turn, char playerInput[2][10][10][3], char fogPlayerInput[2][10][10][3]){
    system("cls"); // clears terminal
    printf("\n\tPlayer %d's Board: %-50sFog of War\n\n", turn + 1, player[turn]); // header display, using fixed width Field

        for (int j = 0; j < 10; j++) // current player line
            printf("+----");
        printf("+\t"); // print the last line and tab over for second grid

        for (int j = 0; j < 10; j++) // opponent player line
            printf("+----");
        printf("+\n"); // Print vertical sides of each cell


    for (int i = 0; i < 10; i++) {// Print top border of each cell
        if(screenShake && (i % 2 == 0)) // screenshake code
            printf("  "); // 2 space offset for the screenshake

        for (int j = 0; j < 10; j++) // current players line
            printf("| %s ", playerInput[turn][i][j]);
        printf("|\t"); // Print vertical sides of each cell

        for (int j = 0; j < 10; j++)  // opponent players lines
            printf("| %s ", fogPlayerInput[turn][i][j]);
        printf("|\n");

        if(screenShake && (i % 2 == 0)) // screenshake code
            printf("  "); // 2 space offset for the screenshake

        // note to self, insert data on the second for loop somewhere in the middle, workout line spacing and such later.
        for (int j = 0; j < 10; j++) // Print bottom border of the last row
            printf("+----");
        printf("+\t"); // last line for the current players layout

        for (int j = 0; j < 10; j++) // Print bottom border of the last row
            printf("+----");
        printf("+\n"); // last "+" before newline
    }

    //printf("\nScore: %d\n", score); //change for later
}

// Function for handling user input and moving around the board

void getUserBoatPlacement(char playerData[2][10][10][3], char fogPlayerInput[2][10][10][3],
                          char boardPieces[5][3], char playerName[2][100], int turn, int boatLength[5]){

    //NEED FEATURE FOR USER TO BE ABLE TO ESCAPE IF THEY GET STUCK

    char input, orientation,  duckedCell[3] = "  ";
    int hori, vert, newVert, newHori, valid;

    for(int i = 0; i < 5; i++){
        selectionStart:
        input = 0; // reset the input so while loop triggers again
        hori = 0; // reset everytime NEED TO MAKE SURE IF USER PLACES BOAT AT ORIGIN WE FILTER FOR THAT
        vert = 0;
        newHori = hori;
        newVert = vert;
        strcpy(duckedCell, playerData[turn][vert][hori]); // copy the default location into the duckedCell
        strcpy(playerData[turn][vert][hori], "[]"); //user cursor

        while(input != 'q'){
            displayBoard(playerName, 0, turn, playerData, fogPlayerInput); // show placement
            printf("\nEnter a direction with W/A/S/D, Q when finished\n");
            scanf(" %c", &input); // space to get rid of any accidental newline stuff

            strcpy(playerData[turn][vert][hori], duckedCell); // put old cell back

            if(input == 'w' || input == 'W')
                newVert--; // make switch statement later
            else if(input == 's' || input == 'S')
                newVert++;
            else if(input == 'a' || input == 'A')
                newHori--;
            else if(input == 'd' || input == 'D')
                newHori++;
            else if(input != 'q')
                continue; //if user quits they don't have to change the state

            if(newVert < 0)
                newVert = 0; //checking is user input is valid or not by forcing bounds
            if(newVert > 9)
                newVert = 9;
            if(newHori < 0)
                newHori = 0;
            if(newHori > 9)
                newHori = 9;

            if(strcmp(playerData[turn][newVert][newHori], "  ") != 0){ //checking the validity of the sqaure
                printf("This Cell is Taken, Try Again!\n");
                continue;
            }
            strcpy(playerData[turn][vert][hori], duckedCell); // erase old cursor
            vert = newVert;
            hori = newHori;
            strcpy(duckedCell, playerData[turn][vert][hori]);
            strcpy(playerData[turn][vert][hori], "[]"); //user cursor
        }
        printf("Place Boat %s (Length %d). Enter H for horizontal and V for vertical\n", boardPieces[i], boatLength[i]);
        scanf(" %c", &orientation);

        valid = 0; // checking for validity

        while(valid == 0){
            valid = 1; // only changes if invalid
            for(int k = 1; k < boatLength[i]; k++){ // CHECKING BEFORE PLACING
                // If triggered on V and H then need escape sequence
                if(orientation == 'V' || orientation == 'v'){
                    if((vert + boatLength[i] - 1) >= 10){
                        valid = 0;
                        break;
                    }
                    if(strcmp(playerData[turn][vert + k][hori], "  ") != 0){
                        valid = 0;
                        break;
                    }
                }else if(orientation == 'H' || orientation == 'h'){
                    if((hori + boatLength[i] - 1) >= 10){
                        valid = 0;
                        break;
                    }
                    if(strcmp(playerData[turn][vert][hori + k], "  ") != 0){
                        valid = 0;
                        break;
                    }
                }else{ //invalid input and not invalid placement
                    valid = 0;
                    break;
                    }
                }

                if (!valid){
                    printf("Invalid Input Try Again or Type 'X' if Stuck\n"); //getting user input and trying again
                    scanf(" %c", &orientation);
                    if(orientation == 'X' || orientation == 'x'){ // resets values
                        strcpy(playerData[turn][vert][hori], duckedCell); //replace with old list item
                        goto selectionStart; // GOING BACK TO SELECTION
                    }
                }
        }
        for(int j = 0; j < boatLength[i]; j++){ // place boats now
            if(orientation == 'V' || orientation == 'v')
                strcpy(playerData[turn][vert + j][hori], boardPieces[i]); // place data

            else if (orientation == 'H' || orientation == 'h')
                strcpy(playerData[turn][vert][hori + j], boardPieces[i]); // place data
        }
        displayBoard(playerName, 0, turn, playerData, fogPlayerInput); // display
    }
}

void pause(char player[2][100]){
    char pauseIn;
    battleShipPause_ASCII();
    printf("\n\n\n\t\t\t   Enter anything except 'L' to Unpause \n\n");
    printf("If player %s would like to surrender, enter 'L'", player[2]);
    scanf(" %c", &pauseIn);
    if(pauseIn == 'L' || pauseIn == 'l'){}
        // INSERT WIN CONDITION WILL NEED TO USE POINTER TO ACCESS AND CHANGE
}



// ASCII ART START HERE

void battleShipCover_ASCII(){
    printf("    ______     ______     ______   ______   __         ______    \n");
    printf("   /\\  == \\   /\\  __ \\   /\\__  _\\ /\\__  _\\ /\\ \\       /\\  ___\\   \n");
    printf("   \\ \\  __<   \\ \\  __ \\  \\/_/\\ \\/ \\/_/\\ \\/ \\ \\ \\____  \\ \\  __\\   \n");
    printf("    \\ \\_____\\  \\ \\_\\ \\_\\    \\ \\_\\    \\ \\_\\  \\ \\_____\\  \\ \\_____\\ \n");
    printf("     \\/_____/   \\/_/\\/_/     \\/_/     \\/_/   \\/_____/   \\/_____/ \n");
    printf("                   ______     __  __     __     ______           \n");
    printf("                  /\\  ___\\   /\\ \\_\\ \\   /\\ \\   /\\  == \\          \n");
    printf("                  \\ \\___  \\  \\ \\  __ \\  \\ \\ \\  \\ \\  _-/          \n");
    printf("                   \\/\\_____\\  \\ \\_\\ \\_\\  \\ \\_\\  \\ \\_\\            \n");
    printf("                    \\/_____/   \\/_/\\/_/   \\/_/   \\/_/            \n");
}

void battleShipPause_ASCII(){
    printf("______       _   _   _        _____ _     _        \n");
    printf("| ___ \\     | | | | | |      /  ___| |   (_)       \n");
    printf("| |_/ / __ _| |_| |_| | ___  \\ `--.| |__  _ _ __   \n");
    printf("| ___ \\/ _` | __| __| |/ _ \\  `--. \\ '_ \\| | '_ \\  \n");
    printf("| |_/ / (_| | |_| |_| |  __/ /\\__/ / | | | | |_) | \n");
    printf("\\____/ \\__,_|\\__|\\__|_|\\___| \\____/|_| |_|_| .__/  \n");
    printf("                                           | |     \n");
    printf("                                           |_|     \n");
}

void winScreen_ASCII(int booleanTurn){
if(booleanTurn){
     printf(" ________  ___       ________      ___    ___ _______   ________          _________  ___       __   ________     \n");
    printf("|\\   __  \\|\\  \\     |\\   __  \\    |\\  \\  /  /|\\  ___ \\ |\\   __  \\        |\\___   ___\\\\  \\     |\\  \\|\\   __  \\    \n");
    printf("\\ \\  \\|\\  \\ \\  \\    \\ \\  \\|\\  \\   \\ \\  \\/  / | \\   __/|\\ \\  \\|\\  \\       \\|___ \\  \\_\\ \\  \\    \\ \\  \\ \\  \\|\\  \\   \n");
    printf(" \\ \\   ____\\ \\  \\    \\ \\   __  \\   \\ \\    / / \\ \\  \\_|/_\\ \\   _  _\\           \\ \\  \\ \\ \\  \\  __\\ \\  \\ \\  \\\\\\  \\  \n");
    printf("  \\ \\  \\___|\\ \\  \\____\\ \\  \\ \\  \\   \\/  /  /   \\ \\  \\_|\\ \\ \\  \\\\  \\|           \\ \\  \\ \\ \\  \\|\\__\\_\\  \\ \\  \\\\\\  \\ \n");
    printf("   \\ \\__\\    \\ \\_______\\ \\__\\ \\__\\__/  / /      \\ \\_______\\ \\__\\\\ _\\            \\ \\__\\ \\ \\____________\\ \\_______\\\n");
    printf("    \\|__|     \\|_______|\\|__|\\|__|\\___/ /        \\|_______|\\|__|\\|__|            \\|__|  \\|____________|\\|_______|\n");
    printf("                                 \\|___|/                                                                         \n");
    printf("                                                                                                                 \n");
    printf("                                                                                                                 \n");
    printf("                                ___       __   ___  ________   ________                                          \n");
    printf("                               |\\  \\     |\\  \\|\\  \\|\\   ___  \\|\\   ____\\                                         \n");
    printf("                               \\ \\  \\    \\ \\  \\ \\  \\ \\  \\\\ \\  \\ \\  \\___|_                                        \n");
    printf("                                \\ \\  \\  __\\ \\  \\ \\  \\ \\  \\\\ \\  \\ \\_____  \\                                       \n");
    printf("                                 \\ \\  \\|\\__\\_\\  \\ \\  \\ \\  \\\\ \\  \\|____|\\  \\                                      \n");
    printf("                                  \\ \\____________\\ \\__\\ \\__\\\\ \\__\\____\\_\\  \\                                     \n");
    printf("                                   \\|____________|\\|__|\\|__| \\|__|\\_________\\                                    \n");
    printf("                                                                 \\|_________|                                    \n");
    printf("                                                                                                                 \n");
    printf("                                                                                                                 \n");
} else if(!booleanTurn){
    printf(" ________  ___       ________      ___    ___ _______   ________          ________  ________   _______          \n");
    printf("|\\   __  \\|\\  \\     |\\   __  \\    |\\  \\  /  /|\\  ___ \\ |\\   __  \\        |\\   __  \\|\\   ___  \\|\\  ___ \\         \n");
    printf("\\ \\  \\|\\  \\ \\  \\    \\ \\  \\|\\  \\   \\ \\  \\/  / | \\   __/|\\ \\  \\|\\  \\       \\ \\  \\|\\  \\ \\  \\\\ \\  \\ \\   __/|        \n");
    printf(" \\ \\   ____\\ \\  \\    \\ \\   __  \\   \\ \\    / / \\ \\  \\_|/_\\ \\   _  _\\       \\ \\  \\\\\\  \\ \\  \\\\ \\  \\ \\  \\_|/__      \n");
    printf("  \\ \\  \\___|\\ \\  \\____\\ \\  \\ \\  \\   \\/  /  /   \\ \\  \\_|\\ \\ \\  \\\\  \\|       \\ \\  \\\\\\  \\ \\  \\\\ \\  \\ \\  \\_|\\ \\     \n");
    printf("   \\ \\__\\    \\ \\_______\\ \\__\\ \\__\\__/  / /      \\ \\_______\\ \\__\\\\ _\\        \\ \\_______\\ \\__\\\\ \\__\\ \\_______\\    \n");
    printf("    \\|__|     \\|_______|\\|__|\\|__|\\___/ /        \\|_______|\\|__|\\|__|        \\|_______|\\|__| \\|__|\\|_______|    \n");
    printf("                                 \\|___|/                                                                         \n");
    printf("                                                                                                                 \n");
    printf("                                                                                                                 \n");
    printf("                                ___       __   ___  ________   ________                                         \n");
    printf("                               |\\  \\     |\\  \\|\\  \\|\\   ___  \\|\\   ____\\                                        \n");
    printf("                               \\ \\  \\    \\ \\  \\ \\  \\ \\  \\\\ \\  \\ \\  \\___|_                                       \n");
    printf("                                \\ \\  \\  __\\ \\  \\ \\  \\ \\  \\\\ \\  \\ \\_____  \\                                      \n");
    printf("                                 \\ \\  \\|\\__\\_\\  \\ \\  \\ \\  \\\\ \\  \\|____|\\  \\                                     \n");
    printf("                                  \\ \\____________\\ \\__\\ \\__\\\\ \\__\\____\\_\\  \\                                    \n");
    printf("                                   \\|____________|\\|__|\\|__| \\|__|\\_________\\                                   \n");
    printf("                                                                 \\|_________|                                   \n");
    printf("                                                                                                                 \n");
    printf("                                                                                                                 \n");
}


}

