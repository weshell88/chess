#ifndef BOARD_H
#define BOARD_H

#include<QWidget>
#include<QPainter>
#include<QMouseEvent>
#include<QPushButton>
#include<QString>
#include<QTime>
#include<cmath>
#include <stack>
#include"stone.h"
/**************************************/
/**************************************/
/**************************************/
class Board:public QWidget
{
	Q_OBJECT public:
		explicit Board(QWidget * parent = 0);
	int d=40 ;
	int r=d/2;
	Stone stone[32];
	int selectID;
	bool redturn;
	std::stack < Stone > Log;
	QPushButton *ResetButton;
	QPushButton *RegretButton;
	QPoint center(int c, int r);
	QPoint center(int i);


	/**************************************/
	/*****************画棋盘*********************/
	/**************************************/
	void drawBoard(QPainter & painter);
	void drawStone(QPainter & painter);
	void paintEvent(QPaintEvent *);
	/*********************************/
	/**************************************/
	/**************************************/
	void mouseReleaseEvent(QMouseEvent * e);
	void clickP(QPoint pt);
	virtual void clickCR(int col, int row);
	bool move(int col, int row);
	/**************************************/
	/******************行棋规则*************/
	/**************************************/
	int barrier(int i, int col, int row);
	int barrier(int i, int j);
	int GetID(int col, int row);
	bool checked();
	bool checkR();
	bool checkB();
	bool face();
	bool canmoveJ(int i, int col, int row);
	bool canmovej(int i, int col, int row);
	bool canmovem(int i, int col, int row);
	bool canmovep(int i, int col, int row);
	bool canmoveb(int i, int col, int row);
	bool canmoves(int i, int col, int row);
	bool canmovex(int i, int col, int row);
	bool canmove(int i, int col, int row);

	void Regret();
	void Reset();

signals:
	public slots:
		virtual void RegretB();
	void ResetB();

};
/**************************************/
/**************************************/
/**************************************/


#endif // BOARD_H
