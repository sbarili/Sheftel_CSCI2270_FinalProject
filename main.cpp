/************************************
 * Final Project: Rock-Paper-Scissors
 * Author: Holden Sheftel
 *
 * CSCI 2270 - Spring 2016
 ************************************/

#include <iostream>
#include "game.h"
#include "MoveData.h"
using namespace std;

//print main menu
void printMainMenu()
{
    cout << "What would you like to do?" << endl;
    cout << "==========================" << endl;
    cout << "1. Play Rock-Paper-Scissors" << endl;
    cout << "2. Display data" << endl;
    cout << "3. Change computer's decision process" << endl;
    cout << "0. Exit" << endl;
}

void printDecisionMenu()
{
    cout << "What decision method should be used?" << endl;
    cout << "====================================" << endl;
    cout << "1. Random (default)" << endl;
    cout << "2. Predictive" << endl;
}

int main()
{
    cout << "Welcome to Rock Paper Scissors!" << endl;

    bool exit = false;
    char command;
    int input;
    MoveData data;

    do
    {
        printMainMenu();
        cin >> command;

        switch (command)
        {
            case '1':
                playGame(data);
                break;
            case '2':
                data.displayData();
                break;
            case '3':
                printDecisionMenu();
                cin >> input;
                data.setDecisionType(input);
                break;
            case '0':
                exit = true;
                break;
            /*case 'z':   //for testing
                break;*/
            default:
                cout << "Invalid input." << endl;
                break;
        } //end switch
    } while (!exit);

    return 0;
}
