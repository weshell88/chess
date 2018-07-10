#ifndef STONE_H
#define STONE_H

#include<QString>

class Stone
{
	public:
		enum Type
		{ J, s, x, j, m, p, b };
		Type type;
		int ID;
		int row, col;
		bool alive;
		bool red;
		QString gettext();
		int getValue();
		void init(int i);
};

#endif // STONE_H
