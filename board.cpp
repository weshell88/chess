#include"board.h"

/********************构造*******************/
/**********************绘图*****************************/
void Board::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    drawBoard(painter);
    drawStone(painter);
}
QPoint Board::center(int c, int r)
{
    return QPoint(c * d, r * d);
}
QPoint Board::center(int i)
{
    return center(stone[i].col, stone[i].row);
}
/*****************画棋盘*********************/
void Board::drawBoard(QPainter & painter)
{
    for (int i = 1; i <= 10; i++)
    {
        painter.drawLine(QPoint(d, i * d), QPoint(9 * d, i * d));
    }
    for (int i = 1; i < 10; i++)
    {
        if (i == 1 || i == 9)
        {
            painter.drawLine(QPoint(i * d, d), QPoint(i * d, 10 * d));
        } else
        {
            painter.drawLine(QPoint(i * d, d), QPoint(i * d, 5 * d));
            painter.drawLine(QPoint(i * d, 6 * d), QPoint(i * d, 10 * d));
        }
    }
    painter.drawLine(QPoint(4 * d, d), QPoint(6 * d, 3 * d));
    painter.drawLine(QPoint(6 * d, d), QPoint(4 * d, 3 * d));
    painter.drawLine(QPoint(4 * d, 8 * d), QPoint(6 * d, 10 * d));
    painter.drawLine(QPoint(4 * d, 10 * d), QPoint(6 * d, 8 * d));
}
// *************** 画棋子 *****************//
void Board::drawStone(QPainter & painter)
{
    for (int i = 0; i < 32; i++)
    {
        if (!stone[i].alive)
        {
            continue;
        }
        QPoint c = center(i);
        QRect rect = QRect(c.x() - d / 2, c.y() - d / 2, d, d);
        if (i == selectID)
            painter.setBrush(QColor(Qt::gray));
        else
        {
            painter.setBrush(Qt::yellow);
        }
        painter.setPen(Qt::black);
        painter.drawEllipse(center(i), d / 2, d / 2);
        if (i < 16)
        {
            painter.setPen(Qt::red);
        } else
        {
            painter.setPen(Qt::black);
        }
        painter.setFont(QFont("system"));
        painter.drawText(rect, stone[i].gettext(),
                         QTextOption(Qt::AlignCenter));
    }
}

/*****************行棋规则******************/
void Board::mouseReleaseEvent(QMouseEvent * e)
{
    QPoint pt = e->pos();
    clickP(pt);
}

/****************辅助函数**********************/
int Board::GetID(int col, int row)
{
    int getID = -1;
    for (int i = 0; i < 32; i++)
    {
        if (stone[i].row == row && stone[i].col == col && stone[i].alive)
        {
            getID = i;

            break;
        }
    }
    return getID;
}



void Board::clickP(QPoint pt)
{
    if (pt.x() > 10 * d || pt.y() > 11 * d)
    {
        selectID = -1;
        return;
    }
    int col, row;
    col = (pt.rx() + r) / d;
    row = (pt.ry() + r) / d;
    clickCR(col, row);
}
/**************************************/
/******************走棋函数********************/
/**************************************/
void Board::clickCR(int col, int row)
{
    if (move(col, row))
    {
        redturn = !redturn;
    }
    update();
}

bool Board::move(int col, int row)
{
    int getID = GetID(col, row);
    if (selectID == -1 && getID == -1)
    {
        return false;
    } else if (selectID == -1 && getID != -1)
    {
        if (stone[getID].red == redturn)
        {
            selectID = getID;
            update();
        }
        return false;
    } else if (selectID != -1 && getID == -1)
    {
        if (canmove(selectID, col, row))
        {
            Log.push(stone[selectID]);
            stone[selectID].row = row;
            stone[selectID].col = col;
            return checked();
        }else {
            return false;
        }
    } else if (selectID != -1 && getID != -1)
    {
        if (stone[selectID].red == stone[getID].red)
        {
            selectID = getID;
            return false;
        } else if (canmove(selectID, col, row))
        {
            stone[getID].alive = false;
            Log.push(stone[getID]);
            Log.push(stone[selectID]);
            stone[selectID].row = row;
            stone[selectID].col = col;
            return checked();
        }else{
            return false;
        }
    }
}

/***************** 行棋规则 *****************/

bool Board::checked()
{
    if (face())
    {
        Regret();
        return false;
    } else if (redturn && checkR() || !redturn && checkB())
    {
        Regret();
        return false;
    } else
    {
        selectID = -1;
        return true;
    }
}
bool Board::checkR()
{
    for (int i = 16; i < 32; i++)
    {
        if (stone[i].alive && canmove(i, stone[10].col, stone[10].row))
        {
            return true;
        }
    }
    return false;
}
bool Board::checkB()
{
    for (int i = 0; i < 16; i++)
    {
        if (stone[i].alive && canmove(i, stone[26].col, stone[26].row))
        {
            return true;
        }
    }
    return false;
}

int Board::barrier(int i, int col, int row)
{
    int m = 0;
    if (stone[i].col != col && stone[i].row != row)
    {
        return -1;
    } else if (stone[i].col == col)
    {
        for (int n = 0; n < 32; n++)
        {
            if (stone[n].alive && stone[n].col == col
                    && (stone[n].row - stone[i].row) * (stone[n].row -
                                                        row) < 0)
            {
                m++;
            }
        }
    } else if (stone[i].row == row)
    {
        for (int n = 0; n < 32; n++)
        {
            if (stone[n].alive && stone[n].row == row
                    && (stone[n].col - stone[i].col) * (stone[n].col -
                                                        col) < 0)
            {
                m++;
            }
        }
    }
    return m;
}
int Board::barrier(int i, int j)
{
    return barrier(i, stone[j].col, stone[j].row);
}

bool Board::face()
{
    if (barrier(10,26) == 0)
    {
        return true;
    } else
    {
        return false;
    }
}
/****************行棋规则************/

bool Board::canmoveJ(int i, int col, int row)
{
    if (col > 6 || col < 4 || i < 16 && row > 3 || i > 15 && row < 8)
    {
        return false;
    } else if (abs(stone[i].col - col) + abs(stone[i].row - row) == 1)
    {
        return true;
    } else
    {
        return false;
    }
}
bool Board::canmovej(int i, int col, int row)
{
    if (barrier(i, col, row) == 0)
    {
        return true;
    } else
    {
        return false;
    }
}
bool Board::canmovem(int i, int col, int row)
{
    if (abs(stone[i].col - col) == 1 && abs(stone[i].row - row) == 2)
    {
        if (barrier(i, stone[i].col, row) == 0)
        {
            return true;
        }
    } else if (abs(stone[i].col - col) == 2
               && abs(stone[i].row - row) == 1)
    {
        if (barrier(i, col, stone[i].row) == 0)
        {
            return true;
        }
    } else
    {
        return false;
    }
}
bool Board::canmovep(int i, int col, int row)
{
    int getIDp = GetID(col, row);
    if (getIDp == -1 && barrier(i, col, row) == 0)
    {
        return true;
    } else if (getIDp != -1 && barrier(i, col, row) == 1)
    {
        return true;
    } else
    {
        return false;
    }
}
bool Board::canmoveb(int i, int col, int row)
{
    if (i < 16 && stone[i].row < 6 && stone[i].col == col
            && (row - stone[i].row) == 1)
    {
        return true;
    } else
        if (i > 15 && stone[i].row > 5 && stone[i].col == col
                && (stone[i].row - row) == 1)
        {
            return true;
        } else
            if (i < 16
                    && abs(stone[i].row - row) + abs(stone[i].col - col) == 1
                    && row >= stone[i].row && stone[i].row > 5)
            {
                return true;
            } else
                if (i > 15
                        && abs(stone[i].row - row) + abs(stone[i].col - col) == 1
                        && row <= stone[i].row && stone[i].row < 6)
                {
                    return true;
                } else
                {
                    return false;
                }
}
bool Board::canmoves(int i, int col, int row)
{
    if (i < 16 && col > 3 && col < 7 && row < 4
            && abs(stone[i].row - row) == 1 && abs(stone[i].col - col) == 1)
    {
        return true;
    } else
        if (i > 15 && col > 3 && col < 7 && row > 7
                && abs(stone[i].row - row) == 1
                && abs(stone[i].col - col) == 1)
        {
            return true;
        } else
        {
            return false;
        }
}
bool Board::canmovex(int i, int col, int row)
{
    if (i < 16 && row < 6 && abs(stone[i].row - row) == 2
            && abs(stone[i].col - col) == 2)
    {
        if (GetID((col + stone[i].col) / 2, (row + stone[i].row) / 2)
                == -1)
        {
            return true;
        }

    } else
        if (i > 15 && row > 5 && abs(stone[i].row - row) == 2
                && abs(stone[i].col - col) == 2)
        {
            if (GetID((col + stone[i].col) / 2, (row + stone[i].row) / 2)
                    == -1)
            {
                return true;
            }
        } else
        {
            return false;
        }
}
bool Board::canmove(int i, int col, int row)
{
    int getIDt=GetID(col,row);
    if( getIDt != -1 && stone[i].red == stone[getIDt].red)
    {
        return false;
    }
    switch (stone[i].type)
    {
    case Stone::J:
        canmoveJ(i, col, row);
        break;
    case Stone::j:
        canmovej(i, col, row);
        break;
    case Stone::m:
        canmovem(i, col, row);
        break;
    case Stone::p:
        canmovep(i, col, row);
        break;
    case Stone::b:
        canmoveb(i, col, row);
        break;
    case Stone::s:
        canmoves(i, col, row);
        break;
    case Stone::x:
        canmovex(i, col, row);
        break;
    }
}

void Board::RegretB()
{
    if (!Log.empty())
    {
        Regret();
        redturn = !redturn;
        update();
    }
}
void Board::Regret()
{
    stone[Log.top().ID] = Log.top();
    Log.pop();
    if (Log.empty()) return;
    if (Log.top().alive == false)
    {
        stone[Log.top().ID].alive = true;
        Log.pop();
    }
    selectID=-1;
}
void Board::ResetB()
{
    Reset();
    update();
}
void Board::Reset()
{
    for (int i = 0; i < 32; i++)
    {
        while(!Log.empty()){ Log.pop();}
        stone[i].init(i);
        selectID = -1;
        redturn = true;
    }
}
