#ifndef CHESSBOARD_ZHENGLI
#define CHESSBOARD_ZHENGLI

#include"ChessPoint.h"

class Chessboard
{
public:
	Chessboard(int w=10,int h=10);
	~Chessboard();
	int GetWidth()const{return width;}
	int GetHeight()const{return height;}
	bool SetChessPoint(const ChessPoint& cp,int id);
	//int** const GetPoints()const
	//{
	//	return cb;
	//}
	int GetSum()const
	{
		return sum;
	}
	int GetIdOfPoint(const ChessPoint& cp)const;

private:
	int width;
	int height;
	char *cb;
	int sum;

	bool isPointValid(const ChessPoint& cp)const;
};

#endif


