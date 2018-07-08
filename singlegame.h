#ifndef SINGLEGAME_H
#define SINGLEGAME_H

#include"board.h"

class singleGame:public Board
{
    Q_OBJECT public:
    virtual void clickP(QPoint pt);
    void automove();
    int evaluateB();
    int evaluateR();
    int evaluate(int b);

};
#endif // SINGLEGAME_H
