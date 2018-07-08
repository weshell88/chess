#include "singlegame.h"

void singleGame::clickP(QPoint pt)
{
    if (!redturn)
    {
        return;
    }
    if (pt.x() > 10 * d || pt.y() > 11 * d)
    {
        selectID = -1;
        update();
        return;
    }
    int col, row;
    col = (pt.rx() + r) / d;
    row = (pt.ry() + r) / d;
    click(col, row);
    update();
    if (!redturn)
    {
        automove();
        update();
    }
}
void singleGame::automove()
{
    int ID ;
    int Col;
    int Row;
    int weight;

    // vector < Step > stepvct;
    int weightmax = evaluateB() - evaluateR();
    for (int i = 16; i < 32; i++)
    {
        if(stone[i].alive)
        {
            for (int col = 1; col < 10; col++)
            {
                for (int row = 1; row < 11; row++)
                {
                    selectID = i;
                    if(move(col, row))
                    {
                        weight = evaluateB() -evaluateR();
                        Regret();
                        if (weight >= weightmax)
                        {
                            ID = i;
                            Col = col;
                            Row = row;
                            weightmax = weight;
                        }
                    }
                }
            }
        }
    }
    selectID = ID;
    update();
    move(Col, Row);
    update();
    redturn = !redturn;
}

int singleGame::evaluateB()
{
    return evaluate(16);
}
int singleGame::evaluateR()
{
    return evaluate(0);
}
int singleGame::evaluate(int b)
{
    int weightAll = 0;
    for (int i = 0 + b; i < b + 16; i++)
    {
        weightAll += stone[i].getValue();
    }
    return weightAll;
}
