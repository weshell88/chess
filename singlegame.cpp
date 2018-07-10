#include <QList>
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
    Step bestStep;
    getBestStep(&bestStep);
	moveStep(&bestStep);
}

void singleGame::getAllSteps(QList<Step*>* Steps)
{

	for(int i=16;i<32 ;i++)
	{
		if(!stone[i].alive) continue;
		searchStone(Steps,i);
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
		int getSc=getScore();
		step->score=getSc;
		Steps->append(step);
		Regret();
	}
}

void singleGame::getBestStep(Step* bestStep)
{
    QList<Step*> Steps;
    getAllSteps(&Steps);
	int scoreMax=-10000;
    for(auto iter=Steps.begin();iter!=Steps.end();iter++)
	{   Step* bestStepT=*iter;
		if(bestStepT->score>scoreMax)

		{
			*bestStep=*bestStepT;
			scoreMax=bestStep->score;
		}
	}
    deleteStep(&Steps);
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
	for(int i=0;i<16;i++)
	{
		scoreR += Board::stone[i].getValue();
		scoreB += Board::stone[i+16].getValue();
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
