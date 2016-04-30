/****************
 * MoveData Class
 ****************/

#include <iostream>
#include <random>
#include "MoveData.h"
using namespace std;

MoveData::MoveData()
{
    root = new DecisionNode;
    totalMoves = 0;
    totalWins = 0;
    totalLosses = 0;
    setDecisionType(1);
}

MoveData::~MoveData()
{
    //dtor
}

int MoveData::getTotalMoves()
{
    return totalMoves;
}

void MoveData::setDecisionType(int i)
{
    switch (i)
    {
        case 1:
            decisionType = &MoveData::getRandMove;
            break;
        case 2:
            decisionType = &MoveData::getPredictedMove;
            break;
        default:
            cout << "Invalid decision type. Decision type unchanged." << endl;
    }
}

int MoveData::getComputerMove()
{
    fptr fp = decisionType;
    return (this->*fp)();
}

int MoveData::getRandMove()
{
    random_device seed;     //create seed for random number generator
    minstd_rand randNum(seed());    //create random number generator
    uniform_int_distribution<> dist(1,3);   //distribute results from 1 to 3

    return dist(randNum);
}

int MoveData::getPredictedMove()
{
    DecisionNode* tmpD = root;

    for (Move i : recentMoves) {
        if (tmpD->children.find(i.move) == tmpD->children.end()) {
            break;
        }
        else if (i.win) {
            if (!tmpD->children[i.move]->win) {
                break;
            }
            else {
                tmpD = tmpD->children[i.move]->win;
            }
        }
        else if (!i.win) {
            if (!tmpD->children[i.move]->lose) {
                break;
            }
            else {
                tmpD = tmpD->children[i.move]->lose;
            }
        }
    } //end iteration over recentMoves

    int predictedMove = getMaxMove(tmpD);
    int counterMove = (predictedMove % 3) + 1;
    return counterMove;
}

int MoveData::getMaxMove(DecisionNode* n)
{
    int maxMove = getRandMove();    //move that has occurred max number of times, initially
                                    //chosen randomly in case no moves have been stored here
    int maxNum = 0;     //max number of times a move has appeared

    for (auto i : n->numOfMoveType) {
        if (i.second > maxNum) {
            maxNum = i.second;
            maxMove = nameToNum(i.first);
        }
    }
    return maxMove;
}

void MoveData::enqueueMove(int userMove, bool win)
{
    Move newMove = Move(numToName(userMove), win);

    if (recentMoves.size() == QUEUE_SIZE) {
        recentMoves.pop_front();
    }

    recentMoves.push_back(newMove);
    totalMoves++;
    win ? totalWins++ : totalLosses++;
    moveTypeTotals[newMove.move]++;  //if it does not exist, it will insert it
}

void MoveData::addMove(int userMove)
{
    string newMoveName = numToName(userMove);

    MoveNode* tmpM;
    DecisionNode* tmpD = root;
    for (auto i = recentMoves.begin(); i != recentMoves.end(); ++i) {

        if (tmpD->children.find(i->move) == tmpD->children.end()) {
            tmpM = new MoveNode;
            tmpM->moveName = i->move;
            tmpD->children[i->move] = tmpM;
        }
        else {                                                          //else, tmpM points to appropriate child
            tmpM = tmpD->children[i->move];
        }
        tmpD->numOfMoveType[i->move]++;

        if (i->win && !tmpM->win) {          //if winning move, but NULL win child
            tmpD = new DecisionNode;        //new DecisionNode is allocated
            tmpM->win = tmpD;
        }
        else if (!i->win && !tmpM->lose) {   //if losing node, but NULL lose child
            tmpD = new DecisionNode;        //new DecisionNode is allocated
            tmpM->lose = tmpD;
        }
        else {                              //else tmpD points to appropriate node
            (i->win) ? (tmpD = tmpM->win) : (tmpD = tmpM->lose);
        }
    }

    //increment move sequence data
    tmpD->numOfMoveType[newMoveName]++;
}

void MoveData::displayData()
{
    cout << "Your Stats (does not include ties):" << endl;
    cout << "===================================" << endl;
    cout << "Wins:" << totalWins << endl;
    cout << "Losses:" << totalLosses << endl;
    cout << "Rocks:" << moveTypeTotals["rock"] << endl;
    cout << "Scissors:" << moveTypeTotals["scissors"] << endl;
    cout << "Papers:" << moveTypeTotals["paper"] << endl;
}

string MoveData::numToName(int i)
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

int MoveData::nameToNum(string name)
{
    if (name == "rock")
        return 1;
    else if (name == "paper")
        return 2;
    else if (name == "scissors")
        return 3;
    else
        return 0;
}
