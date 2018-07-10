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
    explicit Board(QWidget * parent = 0):QWidget(parent)
    {
        selectID = -1;
        redturn = true;
        for (int i = 0; i < 32; i++)
        {
            stone[i].init(i);
        }
        ResetButton = new QPushButton("重置", this);
        ResetButton->setGeometry(2 * d, 11 * d, 2 * d, d);
        RegretButton = new QPushButton("悔棋", this);
        RegretButton->setGeometry(6 * d, 11 * d, 2 * d, d);
        QObject::connect(ResetButton, SIGNAL(clicked()), this, SLOT(ResetB()));
        QObject::connect(RegretButton, SIGNAL(clicked()), this,
                SLOT(RegretB()));
    }
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


    // **************************************//
    // *************** 获取棋子 *****************//
    // **************************************//
    int GetID(int col, int row);
    /*********************************/
    /**************************************/
    /**************************************/
    void mouseReleaseEvent(QMouseEvent * e);
    void clickP(QPoint pt);
    /**************************************/
    /******************走棋函数********************/
    /**************************************/
    virtual void clickCR(int col, int row);
    bool move(int col, int row);

    // **************************************//
    // *************** 行棋规则 *****************//
    // **************************************//
    bool checked();
    bool checkR();
    bool checkB();
    bool face();
    int barrier(int i, int col, int row);
    int barrier(int i, int j);
    // **************************************//
    // *************** 将军判断 *****************//
    // **************************************//
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
