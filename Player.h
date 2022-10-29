//
// Created by Bdude on 10/20/2022.
//

#ifndef BATTLESHIP_PLAYER_H
#define BATTLESHIP_PLAYER_H

#include <iostream>
#include <unordered_map>

using namespace std;

class Player {
public:
    unordered_map<char, int> shipsHealth;
    unordered_map<char, string> ships = {
            {'C',"Carrier"},
            {'B',"Battleship"},
            {'D',"Destroyer"},
            {'S', "Submarine"},
            {'P',"Patrol Boat"}
    };
    char shipMap[10][10] = {
            {'_','_','_','_','_','_','_','_','_','_'},
            {'_','_','_','_','_','_','_','_','_','_'},
            {'_','_','_','_','_','_','_','_','_','_'},
            {'_','_','_','_','_','_','_','_','_','_'},
            {'_','_','_','_','_','_','_','_','_','_'},
            {'_','_','_','_','_','_','_','_','_','_'},
            {'_','_','_','_','_','_','_','_','_','_'},
            {'_','_','_','_','_','_','_','_','_','_'},
            {'_','_','_','_','_','_','_','_','_','_'},
            {'_','_','_','_','_','_','_','_','_','_'},
    };
    char attackMap[10][10] = {
            {'_','_','_','_','_','_','_','_','_','_'},
            {'_','_','_','_','_','_','_','_','_','_'},
            {'_','_','_','_','_','_','_','_','_','_'},
            {'_','_','_','_','_','_','_','_','_','_'},
            {'_','_','_','_','_','_','_','_','_','_'},
            {'_','_','_','_','_','_','_','_','_','_'},
            {'_','_','_','_','_','_','_','_','_','_'},
            {'_','_','_','_','_','_','_','_','_','_'},
            {'_','_','_','_','_','_','_','_','_','_'},
            {'_','_','_','_','_','_','_','_','_','_'},
    };
    string letters[10] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J"};
    Player() {
        shipsHealth = {
                {'C',5},
                {'B',4},
                {'D',3},
                {'S',3},
                {'P',2}
        };
    };
    //Helper methods
    int convertToY(char letter) {
        letter = (char) toupper(letter);
        int y = 0;
        for(int i=0;i<10;i++) {
            if ( letter == letters[i][0]) {
                y = i;
            }
        }
        return y;
    }
    //Ship placement methods
    void runShipBuildingMenu() {
        char unplacedShips[] = {'C','B','S','D','P'};

        while (true) {

            cout << "Which ship would you like to place?\n";
            int xCount = 0;
            for (int i=0;i<sizeof(unplacedShips);i++) {
                if(unplacedShips[i] != 'X'){
                    cout << unplacedShips[i] << ") " << ships[unplacedShips[i]] << " (" << shipsHealth[unplacedShips[i]] << ") Spaces\n";
                }
                else {
                    xCount++;
                }
            }
            if (xCount == sizeof(unplacedShips)) {
                break;
            }
            cout << ">";
            char choice;
            cin >> choice;
            displayShipMap();
            bool successful = false;
            while (!successful) {
                cout << "Where would you like to place your ship?\nRemember, it cannot overlap with another ship or go out of bounds.\n";
                bool isRight;
                cout << "Will your ship go down or right from your starting point?\n0) Down\n1) Right\n>";
                cin >> isRight;
                char letter;
                cout << "Now for its starting point. Letter:\n>";
                cin >> letter;
                int x;
                cout << "Number:\n>";
                cin >> x;
                successful = placeShip(letter, x, isRight, choice);
            }
            for (int i=0;i<sizeof(unplacedShips);i++) {
                if(unplacedShips[i] == choice) {
                    unplacedShips[i] = 'X';
                    break;
                }
            }

        }

    }
    bool placeShip(char letter,int number,bool right, char ship) {
       int x = number -1;
       int y = convertToY(letter);
       //First ensure if every part of the ship is safe to be placed.
        for(int i=0;i<shipsHealth[ship];i++) {
            bool coordsAreGood = right?validateCoords(x + i,y): validateCoords(x,y + i);
            if (!coordsAreGood) {
                return false;
            }
        }
        //Then actually place the ship.
        for(int i=0;i<shipsHealth[ship];i++) {
            if (right) {
                    shipMap[y][x + i] = ship;
            } else {
                    shipMap[y + i][x] = ship;
            }
        }
        return true;
    }
    bool validateCoords(int x, int y) {
        if(x > 9 || y > 9 || x < 0 || y < 0) {
           cout << "That ship would go out of bounds. Try again.\n";
           return false;
        }
        else if (shipMap[y][x] != '_') {
            cout << "That ship would conflict with another. Try again.\n" ;
            return false;
        }
        else {
            return true;
        }
    }
    //Menu methods
    void displayShipMap() {
        cout << "  1 2 3 4 5 6 7 8 9 10\n";
        for (int y=0;y<10;y++) {
            cout << letters[y] << " ";
            for (int x=0;x<10;x++) {
                cout << shipMap[y][x] << " ";
            }
            cout << "\n";

        }
    }
    void displayAttackMap() {
        cout << "  1 2 3 4 5 6 7 8 9 10\n";
        for (int y=0;y<10;y++) {
            cout << letters[y] << " ";
            for (int x=0;x<10;x++) {
                cout << attackMap[y][x] << " ";
            }
            cout << "\n";
        }
    }
    void runMenu(bool *gameOver) {
        int option = 0;
        while (option<1 || option>4) {
            cout << "1) View Attack Map\n2) View Your Ships\n3) Take Your Shot\n4) Save and Exit\n>";
            cin >> option;

            cout << "------------------\n";
            switch (option) {
                case 1:
                    displayAttackMap();
                    option = 0;
                    break;
                case 2:
                    displayShipMap();
                    option = 0;
                    break;
                case 3:
                    continue;
                case 4:
                    *gameOver = !*gameOver;
                    cout << (*gameOver?"The game will save and end after this round.\n":"The game will not end after this round.\n");
                    option = 0;
                    break;
                default:
                    cout << "Your response was invalid. Try again\n";
                    if (!cin) {
                        cin.clear();
                        cin.ignore(100,'\n');
                    }
            }
        }
    }
    //Gameplay methods
    bool attackShip(char letter,int number) {
        int x = number -1;
        int y = convertToY(letter);
        char ship = shipMap[y][x];
        bool hit = false;
        if (ship == 'X' || ship == 'O') {
            cout << "Whoops! You already shot there.";
        }
        if (ship != '_') {
            shipsHealth[ship] = shipsHealth[ship] - 1;
            cout << "You made a hit on the " << ships[ship] << ".\n";
            if(shipsHealth[ship] == 0) {
                cout << "You sunk the " << ships[ship] << ".\n";
            }
            hit = true;
            shipMap[y][x] = 'X';
        }
        else {
            cout << "You missed!" << "\n";
            shipMap[y][x] = 'O';
        }
        return hit;
    }
    void trackHit(char letter, int number, bool hit) {
        int y = convertToY(letter);
        attackMap[y][number-1] = hit?'X':'O';
    }
    //Save game methods
    string shipMapToString() {
        string out = "";
        for(int i=0;i<100;i++) {
            int x = i % 10;
            int y = i / 10;
            out += shipMap[y][x];
        }
        return out;
    }
    void stringToShipMap(string source) {
        for (int i=0;i<100;i++) {
            int x = i % 10;
            int y = i / 10;
            shipMap[y][x] = source[i];
        }

    }
    string attackMapToString() {
        string out = "";
        for(int i=0;i<100;i++) {
            int x = i % 10;
            int y = i / 10;
            out += attackMap[y][x];
        }
        return out;
    }
    void stringToAttackMap(string source) {
        for (int i=0;i<100;i++) {
            int x = i % 10;
            int y = i / 10;
            attackMap[y][x] = source[i];
        }

    }
};


#endif //BATTLESHIP_PLAYER_H
