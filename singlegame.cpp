#include "QList"
#include "singlegame.h"
#include "stone.h"

void singleGame::clickCR(int col,int row)
{
    if (!this->redturn) return;
    Board::clickCR(col, row);
    update();
    if (!this->redturn)
    {
        automove();
        update();
        selectID=-1;
        redturn=!redturn;
    }
}
void singleGame::automove()
{
    QList<Step*> Steps;
    Step bestStep;
    getAllSteps(&Steps);
    getBestStep(&Steps,&bestStep);
    moveStep(&bestStep);
    deleteStep(&Steps);
}
void singleGame::getAllSteps(QList<Step*>* Steps)
{
    for(int i=16;i<32 ;i++)
    {
        if(!stone[i].alive) continue;
        for(int col=1;col<10;col++)
        {
            for(int row=1;row<11;row++)
            {
                selectID=i;
                int getID=GetID(col,row);
                if(move(col,row))
                {
                    Step* step=new Step;
                    step->movedID=i;
                    step->killID=getID;
                    step->colFrom=Log.top().col;
                    step->rowFrom=Log.top().row;
                    step->colTo=col;
                    step->rowTo=row;
                    step->score=getScore();
                    Steps->append(step);
                    Regret();
                }
            }
        }
    }
}
void singleGame::getBestStep(QList<Step*>* Steps,Step* bestStep)
{
    int scoreMax=-10000;
    for(auto iter=Steps->begin();iter!=Steps->end();iter++)
    {   Step* bestStepT=*iter;
        if(bestStepT->score>=scoreMax)
        {
            *bestStep=*bestStepT;
            scoreMax=bestStep->score;
        }
    }
}
void singleGame::moveStep(Step* bestStep)
{
    selectID=bestStep->movedID;
    move(bestStep->colTo,bestStep->rowTo);
}
void singleGame::deleteStep(QList<Step*>* Steps)
{
    for(auto iter=Steps->begin();iter!=Steps->end();iter++)
    {
        delete *iter;
    }
    Steps->clear();
}


int singleGame::getScore()
{
    int scoreR=0;
    int scoreB=0;
    for(int i=1;i<16;i++)
    {
        scoreR += stone[i].getValue();
        scoreB += stone[i+16].getValue();
    }
    return scoreB-scoreR;
}
void singleGame::RegretB()
{
    if(!redturn)return;
    if (Log.empty())return;
        Regret();
        Regret();
        update();
}
