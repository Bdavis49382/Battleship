#include <iostream>
#include <fstream>
#include "Player.h"

bool validateLetter(char letter) {
    letter = (char) toupper(letter);
    if (!cin) {
        cin.clear();
        cin.ignore(100,'\n');
        cout << "That input was invalid.";
        return true;
    }
    else if (letter == ' ') {
        return true;
    }
    else if (letter < 'A' || letter > 'J' ) {
       cout << "That letter was not in the valid range. Choose something between A-J\n";
       return true;
    }
    return false;
}
bool validateNumber(int number) {
    if (!cin) {
        cin.clear();
        cin.ignore(100,'\n');
        cout << "That input was invalid.\n";
        return true;
    }
    else if (number < 0 || number > 10) {
       cout << "That number was not in the valid range. Try something between 1-10.\n";
    }
    return number == 0;
}
int main() {
    Player player1;
    Player player2;

    //Start the game by selecting the way the maps will be generated.

    int choice;
    while(true) {
        cout << "Welcome to Battleship!\n1) Debug Mode\n2) Load Game\n3) New Game\n>";
        cin >> choice;
        cin.ignore(100,'\n');
        if (!cin) {
            cin.clear();
            cin.ignore(100,'\n');
            cout << "That was not a valid option.\n";
        }
        else {
            break;
        }
    }

    fstream SaveFile("gameSave.txt");

    fstream templateFile("templateShipMap.txt");
    string text;
    int lineCounter = 0;
    switch (choice) {
        case 1:
            while(getline( templateFile, text)) {
                player1.stringToShipMap(text);
                player2.stringToShipMap(text);
            }
            break;
        case 2:
            while(getline( SaveFile, text)) {
                switch (lineCounter) {
                    case 0:
                        player1.stringToShipMap(text);
                        break;
                    case 1:
                       player2.stringToShipMap(text);
                        break;
                    case 2:
                       player1.stringToAttackMap(text);
                       break;
                    case 3:
                        player2.stringToAttackMap(text);
                        break;
                }
                lineCounter++;
            }
            break;
        case 3:
            player1.runShipBuildingMenu();
            player2.runShipBuildingMenu();
            break;
        default:
            player1.runShipBuildingMenu();
            player2.runShipBuildingMenu();
    }
    templateFile.close();



    //Start game process.
    bool gameOver = false;
    while (!gameOver) {

        //Player 1 starts.
        cout << "\n\n\n\nPlayer 1: Begin Playing \n";
        player1.runMenu(&gameOver);

        //Player 1 shoots.
        int number = 0;
        char letter = ' ';
        while (validateLetter(letter)) {
            cout << "Letter: \n>";
            cin >> letter;
            cin.ignore(100,'\n');
        }
        while (validateNumber(number)) {
            cout << "Number: \n>";
            cin >> number;
            cin.ignore(100,'\n');
        }
        bool hit = player2.attackShip(letter, number);
        player1.trackHit(letter,number, hit);

        //Player 2 plays.
        cout << "\n\n\n\nPlayer 2: Begin Playing \n";
        player2.runMenu(&gameOver);

        //Player 2 shoots.
        letter = ' ';
        number = 0;
        while(validateLetter(letter)) {
            cout << "Letter: \n>";
            cin >> letter;
            cin.ignore(100,'\n');
        }
        while(validateNumber(number)) {
            cout << "Number: \n>";
            cin >> number;
            cin.ignore(100,'\n');
        }
        hit = player1.attackShip(letter, number);
        player2.trackHit(letter, number, hit);

    }

    //Save game.
    SaveFile << player1.shipMapToString();
    SaveFile << "\n";
    SaveFile << player2.shipMapToString();
    SaveFile << "\n";
    SaveFile << player1.attackMapToString();
    SaveFile << "\n";
    SaveFile << player2.attackMapToString();

    SaveFile.close();

    return 0;

}