#include"stone.h"
QString  Stone::gettext()
{
    switch (this->type)
    {
    case j:return "车";
    case m:return "马";
    case p:return "炮";
    case b:return "兵";
    case J:return "将";
    case s:return "士";
    case x:return "象";
    }
}
int  Stone::getValue()
{
    if (this->alive)
    {
        switch (this->type)
        {
        case j:return 100;
        case m:return 50;
        case p:return 50;
        case b:return 20;
        case J:return 10000;
        case s:return 30;
        case x:return 30;
        }
    } else
    {
        return 0;
    }
}
void  Stone::init(int i)
{
    struct
    {
        int r, c;
        Type t;
    } pos[16] =
    {
    {1, 1, j},
    {1, 9, j},
    {1, 2, m},
    {1, 8, m},
    {3, 2, p},
    {3, 8, p},
    {1, 3, x},
    {1, 7, x},
    {1, 4, s},
    {1, 6, s},
    {1, 5, J},
    {4, 1, b},
    {4, 3, b},
    {4, 5, b},
    {4, 7, b},
    {4, 9, b}};
    ID = i;
    alive = true;
    if (i < 16)
    {
        red = true;
        row = pos[i].r;
        col = pos[i].c;
        type = pos[i].t;
    } else
    {
        red = false;
        row = 11 - pos[i - 16].r;
        col = 10 - pos[i - 16].c;
        type = pos[i - 16].t;
    }
}
