#include <QList>
#include <QTimer>
#include "singlegame.h"
#include "stone.h"

void singleGame::clickCR(int col,int row)
{
    if (!this->redturn) return;
    Board::clickCR(col, row);
    update();
    if (!this->redturn)
    {
        QTimer::singleShot(10,this,SLOT(automove()));
        //automove();
    }
}
void singleGame::automove()
{
    Step bestStep;
    getBestStep(&bestStep,2);
    moveStep(&bestStep);
    update();
    selectID=-1;
    redturn=!redturn;
}
void singleGame::getBestStep(Step* BestStep,int level)
{
    QList<Step*> Steps;
    getAllSteps(&Steps);
    int MaxScore=-10000;
    while (Steps.count())
    {
        Step* stepTemp=Steps.last();
        Steps.removeLast();
        moveStep(stepTemp);
        stepTemp->score=getMinScore(level);
        Regret();
        if(stepTemp->score>MaxScore)
        {
            *BestStep=*stepTemp;
            MaxScore=stepTemp->score;
        }else
        {
            delete stepTemp;
        }
    }

}
void singleGame::getAllSteps(QList<Step*>* Steps)
{
    int head,end;
    if(redturn)
    {
        head=0;end=16;
    }else
    {
        head=16;end=32;
    }
    for(int i=head;i<end ;i++)
    {
        if(!stone[i].alive) continue;
        searchStone(Steps,i);
    }
    if(Steps->count()==0)
    {

    }
}
int  singleGame::getMinScore(int level)
{
    if(level==0) return getScore();
    QList<Step*> Steps;
    getAllSteps(&Steps);
    int MinScore=10000;
    while (Steps.count())
    {
        Step* stepTemp=Steps.last();
        Steps.removeLast();
        moveStep(stepTemp);
        stepTemp->score=getMaxScore(level-1);
        if(stepTemp->score>MinScore)
        {
            MinScore=stepTemp->score;
        }else {
            delete stepTemp;
        }
        Regret();
    }
    return MinScore;

}
int  singleGame::getMaxScore(int level)
{
    if(level==0) return getScore();
    QList<Step*> Steps;
    getAllSteps(&Steps);
    int MaxScore=-10000;
    while (Steps.count())
    {
        Step* stepTemp=Steps.last();
        Steps.removeLast();
        moveStep(stepTemp);
        stepTemp->score=getMinScore(level-1);
        Regret();
        if(stepTemp->score>MaxScore)
        {
            MaxScore=stepTemp->score;
        }else
        {
            delete stepTemp;
        }
    }
    return MaxScore;
}
int singleGame::getScore()
{
    int scoreR=0;
    int scoreB=0;
    for(int i=0;i<16;i++)
    {
        scoreR += Board::stone[i].getValue();
        scoreB += Board::stone[i+16].getValue();
    }
    return scoreB-scoreR;
}

/************help funtion***********/


void singleGame::moveStep(Step* bestStep)
{
    selectID=bestStep->movedID;
    move(bestStep->colTo,bestStep->rowTo);
}

void singleGame::saveStep(QList<Step*>* Steps,int i,int col,int row)
{
    selectID=i;
    int ID=GetID(col,row);
    if(move(col,row))
    {   update();
        Step* step=new Step;
        step->movedID=i;
        step->killID=ID;
        step->colFrom=Log.top().col;
        step->rowFrom=Log.top().row;
        step->colTo=col;
        step->rowTo=row;
        step->score=getScore();
        Steps->append(step);
        Regret();
    }
}
void  singleGame::searchStone(QList<Step*>* Steps,int i)
{
    switch (stone[i].type)
    {
    case Stone::p:searchL(Steps,i) ;break;
    case Stone::j:searchL(Steps,i) ;break;
    case Stone::m:searchC(Steps,i,2) ;break;
    case Stone::b:searchC(Steps,i,1) ;break;
    case Stone::J:searchC(Steps,i,1) ;break;
    case Stone::s:searchC(Steps,i,1) ;break;
    case Stone::x:searchC(Steps,i,2) ;break;

    }
}
void singleGame::searchL(QList<Step*>* Steps,int i)
{
    for(int row=1;row<11;row++)
    {
        saveStep(Steps,i,stone[i].col,row);
    }
    for(int col=1;col<10;col++)
    {
        saveStep(Steps,i,col,stone[i].row);
    }
}

void singleGame::searchC(QList<Step*>* Steps,int i,int d)
{
    for(int col=stone[i].col-d;col<=stone[i].col+d;col++)
    {
        if(col>9) break;
        if(col<1) continue;
        for(int row=stone[i].row-d;col<=stone[i].row+d;row++)
        {
            if(row>10) break;
            if(row<1) continue;
            saveStep(Steps,i,col,row);
        }
    }
}

void singleGame::RegretB()
{
    if(!redturn)return;
    if (Log.empty())return;
    Regret();
    Regret();
    update();
}
