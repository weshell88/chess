#ifndef SINGLEGAME_H
#define SINGLEGAME_H

#include <QList>
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
    virtual	void automove();
		void getBestStep(QList<Step*>* Steps,Step* stp);
		void getAllSteps(QList<Step*>* Steps);
		void saveStep(QList<Step*>* Steps,int i,int col,int row);
		void moveStep(Step* stp);
		void deleteStep(QList<Step*>* Steps);
		void searchStone(QList<Step*>* Steps,int i);
		void searchL(QList<Step*>* Steps,int i);
		void searchC(QList<Step*>* Steps,int i,int d);
		int getScore();

        void    getNewScore(QList<Step*>* Steps);
        void    getAllStepsR(QList<Step*>* Steps);
        void    getBestStepR(QList<Step*>* Steps,Step* stp);

signals:
		public slots:
			void RegretB();
};
#endif // SINGLEGAME_H
