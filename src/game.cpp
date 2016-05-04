/*****************************
 * Functions allowing gameplay
 *****************************/
//ideas used from http://stackoverflow.com/questions/11377117/rock-paper-scissors-determine-win-loss-tie-using-math

#include <iostream>
#include "game.h"
using namespace std;

void playGame(MoveData &data)
{
    bool exit = false;
    char userMove;
    int computerMove;

    do
    {
        cout << "Rock...Paper...Scissors...SHOOT!" << endl;
        cout << "================================" << endl;
        cout << "1. Rock" << endl;
        cout << "2. Paper" << endl;
        cout << "3. Scissors" << endl;
        cout << "0. Exit" << endl;
        cin >> userMove;                    //get user move

        switch (userMove)
        {
            case '1':
            case '2':
            case '3':
                computerMove = data.getComputerMove();  //get computer's move
                processMove(userMove, computerMove, data);
                break;
            case '0':
                exit = true;
                break;
            default:
                cout << "Invalid input" << endl;
                break;
        }
    } while (!exit);
}

//processes the move being made
void processMove(int userMove, int computerMove, MoveData &data)
{
    bool win;

    //if there is a tie
    if (userMove == computerMove) {
        cout << "You both threw " << numToName(userMove) << ". Tie!" << endl;
        return;
    } //end tie
    else {
        if ((userMove - computerMove + 3) % 3 == 1) {   //added 3 to keep remainder positive
            win = true;
            cout << numToName(userMove) << " beats " << numToName(computerMove) << ". You win!" << endl;
        }
        else {
            win = false;
            cout << numToName(computerMove) << " beats " << numToName(userMove) << ". You lose!" << endl;
        }

        if (data.getTotalMoves() >= QUEUE_SIZE) {
            data.addMove(userMove);
        }

        data.enqueueMove(userMove, win);
    }
}

string numToName(int i)
{
    switch (i) {
        case 1:
            return "rock";
        case 2:
            return "paper";
        case 3:
            return "scissors";
        default:
            return "Error: There is no lizard or Spock";
    }
}
