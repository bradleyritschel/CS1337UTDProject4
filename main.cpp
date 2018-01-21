//
//  main.cpp
//  bsr160130_Project4
//
//  Created by Bradley Ritschel on 11/15/17.
//  Copyright © 2017 Bradley Ritschel. All rights reserved.
//  CS 1337.503
//

#include <iostream>
#include <cstdlib>

using namespace std;

int validateInput(int &input, const int min, const int max) { //input is passed and interval of acceptable numerical input must be given
    //We are taking a string in for ease of use and so that 1,000 with a comma is acceptable
    cin >> input;
    
    while (cin.fail() || input < min || input > max) {
        cout << "You must enter a number between " << min << " and " << max << " " << endl;
        cin.clear();
        cin.ignore(256, '\n');
        cin >> input;
    }
    return input;
}

int getWallet() {
    cout << "Please enter the amount of money you have available to bet: ";
    int wallet = validateInput(wallet, 1, 10000);
    cout << "Your available funds: $" << wallet << endl;
    return wallet;
}

bool askAnotherBet() {
    cout << "Would you like to play another bet? (Y/N): ";
    char answer;
    cin >> answer;
    if (toupper(answer) == 'Y')
        return true;
    else if (toupper(answer) == 'N')
        return false;
    else
        cout << "ERROR: Please enter 'Y' or 'N'" << endl;
        return askAnotherBet();
}

bool askAnotherRound() {
    cout << "Would you like to play another round? (Y/N): ";
    char answer;
    cin >> answer;
    if (toupper(answer) == 'Y')
        return true;
    else if (toupper(answer) == 'N')
        return false;
    else
        cout << "ERROR: Please enter 'Y' or 'N'" << endl;
    return askAnotherRound();
}

int runRound(int funds) {
    
    int** betsArr; //declare pointer to 2D array
    betsArr = new int*[8]; // declare 2D array with 8 elements
    for (int i = 0; i != 8; ++i) // for each element of 2D array, make an array with depth four
        betsArr[i] = new int[4];
    
    int fundsAtStart = funds;
    
    int spin = (rand() % 37);
    
    int red[] = {1,3,5,7,9,12,14,16,18,19,21,23,25,27,30,32,34,36};
    int black[] = {2,4,6,7,10,11,13,15,17,20,22,24,26,29,28,31,33,35};

    int counter = 0;
    
    do {
        cout << "Choose a bet option." << endl
        << "Option 1: Single number (0-36). Pays $35 for each $1 bet." << endl
        << "Option 2: Red or black. Pays $1 for each $1 bet." << endl
        << "Option 3: Odd or even. Pays $1 for reach $1 bet." << endl
        << "Option 4: First 12 (1-12), second 12 (13-24), or third 12 (25-36). Thirds pay $2 for each $1 bet." << endl
        << "Option 5: First half (1-18) or second half (19-36). Halves pay $1 for each $1 bet." << endl
        << "Option 6: First column (1,4,...,34) or Second column (2,5,...,35) or Third column (3,6,...,36). Columns pay $2 for each $1 bet." << endl;
        
        cout << "Your selection: ";
        validateInput(betsArr[counter][0], 1, 6);
        cout << "You chose option " << betsArr[counter][0] << endl;
        
        cout << "How much would you like to place on this bet?: " << endl;
        if (funds < 500)
            validateInput(betsArr[counter][1], 1, funds);
        else
            validateInput(betsArr[counter][1], 1, 500);
        cout << "You bet $" << betsArr[counter][1] << endl;
        funds -= betsArr[counter][1];
        
        if (betsArr[counter][0] == 1) {
            cout << "Choose a single number from 0 to 36" << endl;
            cout << "Your selection: ";
            betsArr[counter][2] = validateInput(betsArr[counter][2], 0, 36);
            cout << "You chose the number " << betsArr[counter][2] << endl;
            if (betsArr[counter][2] == spin)
            funds += ((35 * betsArr[counter][1]) + betsArr[counter][1]);
        }
        if (betsArr[counter][0] == 2) {
            cout << "Choose red (1) or black (2)" << endl;
            cout << "Your selection: ";
            betsArr[counter][2] = validateInput(betsArr[counter][2], 1, 2);
            if (betsArr[counter][2] == 1) {
                cout << "You chose red" << endl;
                for(int i=0; i<18; i++) {
                    if (spin == red[i])
                        funds += (betsArr[counter][1] + betsArr[counter][1]);
                }
            }
            else if (betsArr[counter][2] == 2) {
                cout << "You chose black" << endl;
                for(int i=0; i<18; i++) {
                    if (spin == black[i])
                        funds += (betsArr[counter][1] + betsArr[counter][1]);
                }
            }
        }
        if (betsArr[counter][0] == 3) {
            cout << "Choose odd (1) or even (2)" << endl;
            cout << "Your selection: ";
            betsArr[counter][2] = validateInput(betsArr[counter][2], 1, 2);
            if (betsArr[counter][2] == 1) {
                cout << "You chose odd" << endl;
                if ((spin % 2) == 1)
                    funds += (betsArr[counter][1] + betsArr[counter][1]);
            }
            else if (betsArr[counter][2] == 2) {
                cout << "You chose even" << endl;
                if ((spin % 2) == 0)
                    funds += (betsArr[counter][1] + betsArr[counter][1]);
            }
        }
        if (betsArr[counter][0] == 4) {
            cout << "Choose a third (1,2,3)" << endl;
            cout << "Your selection: ";
            betsArr[counter][2] = validateInput(betsArr[counter][2], 1, 3);
            cout << "You chose third " << betsArr[counter][2] << endl;
            if (betsArr[counter][2] == 1) {
                if ((spin >= 1) && (spin <= 12))
                    funds += ((2 * betsArr[counter][1]) + betsArr[counter][1]);
            }
            else if (betsArr[counter][2] == 2) {
                if ((spin >= 13) && (spin <= 24))
                    funds += ((2 * betsArr[counter][1]) + betsArr[counter][1]);
            }
            else {
                if ((spin >= 25) && (spin <= 36))
                    funds += ((2 * betsArr[counter][1]) + betsArr[counter][1]);
            }
        }
        if (betsArr[counter][0] == 5) {
            cout << "Choose a half (1,2)" << endl;
            cout << "Your selection: ";
            betsArr[counter][2] = validateInput(betsArr[counter][2], 1, 2);
            cout << "You chose half " << betsArr[counter][2] << endl;
            if (betsArr[counter][2] == 1) {
                if ((spin >= 1) && (spin <= 18))
                    funds += (betsArr[counter][1] + betsArr[counter][1]);
            }
            else {
                if ((spin >= 19) && (spin <= 36))
                    funds += (betsArr[counter][1] + betsArr[counter][1]);
            }
        }
        if (betsArr[counter][0] == 6) {
            cout << "Choose a column (1,2,3)" << endl;
            cout << "Your selection: ";
            betsArr[counter][2] = validateInput(betsArr[counter][2], 1, 3);
            cout << "You chose column " << betsArr[counter][2] << endl;
            if (betsArr[counter][2] == 1) {
                if (spin % 3 == 1)
                    funds += ((2 * betsArr[counter][1]) + betsArr[counter][1]);
            }
            else if (betsArr[counter][2] == 2) {
                if (spin % 3 == 2)
                    funds += ((2 * betsArr[counter][1]) + betsArr[counter][1]);
            }
            else {
                if (spin % 3 == 0)
                    funds += ((2 * betsArr[counter][1]) + betsArr[counter][1]);
            }
        }
    counter++;
    }
    while (askAnotherBet() && (funds > 0) && (counter < 8));
    
    for (int i = 0; i != 8; ++i) // for every element of the 2D array, delete the subarray
        delete[] betsArr[i];
    delete[] betsArr; // delete 2D array
    
    int changeInFunds = funds - fundsAtStart;
    
    cout << "The spin was " << spin << endl;
    cout << "Net gain or loss this round: $" << changeInFunds << endl;
    cout << "Funds after last spin: $" << funds << endl;
    return funds;
}

int main() {
    int currentFunds = getWallet();
    int startingFunds = currentFunds;
    do {
        currentFunds = runRound(currentFunds);
    } while (askAnotherRound() && (currentFunds > 0));
    int netChangeInFunds = currentFunds - startingFunds;
    cout << "Thanks for playing! Your net gain or loss from all bets is $" << netChangeInFunds << endl;
    return 0;
}


