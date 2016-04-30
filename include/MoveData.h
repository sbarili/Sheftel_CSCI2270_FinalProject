#ifndef MOVEDATA_H
#define MOVEDATA_H

#include <iostream>
#include <map>
#include <list>     //for an easily iterable queue

#define QUEUE_SIZE 2

//struct for storing a move in the recentMoves queue
struct Move
{
    std::string move;
    bool win;
    Move(){};
    Move(std::string in_move, bool in_win)
    {
        move = in_move;
        win = in_win;
    }
};

struct MoveNode;

struct DecisionNode {
    std::map<std::string,int> numOfMoveType;    //says how many times a move type was chosen here
    std::map<std::string,MoveNode*> children;   //links to children
};

struct MoveNode {
    std::string moveName;
    DecisionNode* win;
    DecisionNode* lose;
};

class MoveData
{
    public:
        MoveData();
        ~MoveData();
        int getTotalMoves();
        void setDecisionType(int i);
        int getComputerMove();
        int getRandMove();
        int getPredictedMove();
        int getMaxMove(DecisionNode* n);
        void enqueueMove(int userMove, bool win);
        void addMove(int userMove);
        std::string numToName(int i);
        int nameToNum(std::string name);
        //void deleteData();
        void displayData();
    protected:
    private:
        DecisionNode* root;
        int totalMoves;
        int totalWins;
        int totalLosses;
        std::map<std::string,int> moveTypeTotals;   //total number of each move
        std::list<Move> recentMoves;    //queue of last 2 moves
        typedef int (MoveData::*fptr)();
        fptr decisionType;
};

#endif // MOVEDATA_H
