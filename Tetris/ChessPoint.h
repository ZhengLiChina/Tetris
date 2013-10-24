#ifndef CHESSPOINT_ZHENGLI
#define CHESSPOINT_ZHENGLI

enum Direction
{
	Up,
	Down,
	Left,
	Right
};

struct ChessPoint
{
	int x;
	int y;
	ChessPoint() {};
	ChessPoint(int a,int b)
	{
		x=a;y=b;
	}
	ChessPoint(Direction dir)
	{
		switch (dir)
		{
		case Up:
			x=0;y=-1;
			break;
		case Down:
			x=0;y=1;
			break;
		case Left:
			x=-1;y=0;
			break;
		case Right:
			x=1;y=0;
			break;
		default:
			break;
		}
	}
};

typedef ChessPoint CP;
ChessPoint operator+(const ChessPoint& l,const ChessPoint& r);
ChessPoint operator-(const ChessPoint& l,const ChessPoint& r);
bool operator==(const ChessPoint& l,const ChessPoint& r);


#endif