#ifndef SINGLEGAME_H
#define SINGLEGAME_H

#include<QList>
#include"board.h"

class singleGame:public Board
{
public:
    struct Step
    {
        int movedID;
        int killID;
        int colFrom;
        int rowFrom;
        int colTo;
        int rowTo;
        int score;
    };
    void clickCR(int col,int row);
    void automove();
    void getBestStep(QList<Step*>* Steps,Step* stp);
    void getAllSteps(QList<Step*>*Steps);
    void moveStep(Step* stp);
    int getScore();
};
#endif // SINGLEGAME_H
