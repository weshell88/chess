#include <QList>
#include <QTimer>
//#include <QDebug>
#include "singlegame.h"
#include "stone.h"

void singleGame::clickCR(int col,int row)
{
    if (!redturn) return;
    Board::clickCR(col, row);
    update();
    if (!redturn)
    {
        QTimer::singleShot(1,this,SLOT(automove()));
        //automove();
    }
}
void singleGame::automove()
{
    deep=0;
    int level=3;
    Step bestStep;
    getBestStep(&bestStep,level);
    selectID=bestStep.movedID;
    update();
    moveStep(&bestStep);
    update();
    selectID=-1;
    redturn=true;
   // qDebug()<< redturn;
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
        int scoreTemp=getMinScore(level,MaxScore);
        retunStep();
        if(scoreTemp>MaxScore)
        {
            *BestStep=*stepTemp;
            MaxScore=scoreTemp;
        }else
        {
            delete stepTemp;
        }
    }

}
void singleGame::getAllSteps(QList<Step*>* Steps)
{
    int head,end;
    if(deep%2==1)
    {
        head=0;end=16;
        //qDebug()<<deep<<"red";
    }else {
        head=16;end=32;
       // qDebug()<<deep<<"blasck";
    }
    for(int i=head;i<end ;i++)
    {
        if(!stone[i].alive) continue;
        searchStone(Steps,i);
    }
    if(Steps->count()==0)
    {
        return;
    }
}

int  singleGame::getMaxScore(int level,int crtMIN_Max)
{

    if(level==0) return getScore();
    QList<Step*> Steps;
    getAllSteps(&Steps);
    int MaxScore=-10000;
    while (Steps.count())
    {
        Step* stepTemp=Steps.last();
        moveStep(stepTemp);
       // qDebug()<<deep;
        Steps.removeLast();
        delete stepTemp;
        int scoreTemp=getMinScore(level-1, MaxScore);
        retunStep();
        if(scoreTemp>=crtMIN_Max)
        {
            while (Steps.count())
            {
                Step* stp= Steps.last();
                Steps.removeLast();
                delete stp;
            }
            return crtMIN_Max;
        }else if(scoreTemp>MaxScore)
        {
            MaxScore=scoreTemp;
        }
    }
    return MaxScore;
}
int  singleGame::getMinScore(int level,int crtMax_Min)
{
    if(level==0) return getScore();
    QList<Step*> Steps;
    getAllSteps(&Steps);
    int MinScore=100000;
    while (Steps.count())
    {
        Step* stepTemp=Steps.last();
        moveStep(stepTemp);
        Steps.removeLast();
        //delete stepTemp;
        int scoreTemp=getMaxScore(level-1,MinScore);
        retunStep();
        if(scoreTemp<=crtMax_Min)
        {
            while (Steps.count())
            {
                Step* stp= Steps.last();
                Steps.removeLast();
                delete stp;
            }
            return crtMax_Min;
        }else if(scoreTemp<MinScore)
        {
            MinScore=scoreTemp;
        }
    }
    return MinScore;
}

/************help funtion***********/

void  singleGame::searchStone(QList<Step*>* Steps,int i)
{
    switch (stone[i].type)
    {
    case Stone::p:
    case Stone::j:
        searchL(Steps,i);
        break;
    case Stone::b:
    case Stone::J:
    case Stone::s:
        searchC(Steps,i,1);
        break;
    case Stone::m:
    case Stone::x:
        searchC(Steps,i,2);
        break;
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

void singleGame::saveStep(QList<Step*>* Steps,int i,int col,int row)
{
    int ID=GetID(col,row);
    selectID=i;
    if(move(col,row)) //必须走后才能检查将军判断
    {   Step* step=new Step;
        step->movedID=i;
        step->killID=ID;
        step->colFrom=Log.top().col;
        step->rowFrom=Log.top().row;
        step->colTo=col;
        step->rowTo=row;
        Steps->append(step);
        Regret();
    }
}

/********************score****************/

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
/*****************move************/
void singleGame::moveStep(Step* bestStep)
{
    selectID=bestStep->movedID;
    move(bestStep->colTo,bestStep->rowTo);
    deep++;
}
void singleGame::retunStep()
{
    Regret();
    deep--;
}

void singleGame::RegretB()
{
    if(!redturn)return;
    if (Log.empty())return;
    Regret();
    Regret();
    update();
}
