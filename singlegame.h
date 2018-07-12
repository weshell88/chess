#ifndef SINGLEGAME_H
#define SINGLEGAME_H

#include <QList>
#include"board.h"

class singleGame:public Board
{ Q_OBJECT
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
    int deep;
    void clickCR(int col,int row);
    void getBestStep(Step* stp,int level);
    void getAllSteps(QList<Step*>* Steps);
    void saveStep(QList<Step*>* Steps,int i,int col,int row);
    void moveStep(Step* stp);
    void retunStep();
    int getScore();
    int getMaxScore(int level,int score);
    int getMinScore(int level,int score);
    /*********help function*********/
    void searchStone(QList<Step*>* Steps,int i);
    void searchL(QList<Step*>* Steps,int i);
    void searchC(QList<Step*>* Steps,int i,int d);


signals:
public slots:
    void automove();
    void RegretB();
};
#endif // SINGLEGAME_H
