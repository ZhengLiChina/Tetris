#include "Chessboard.h"
#include<cstring>


Chessboard::Chessboard(int w,int h)
{
	width=w;
	height=h;
	cb=new char[w*h];//cannot declare int[w][h]. Error

	// for (int i = 0; i < w; ++i)
	// {
	// 	for (int j = 0; j < h; ++j)
	// 	{
	// 		cb[i][j]=0;
	// 	}
	// }
	memset(cb,0,w*h*sizeof(char));
	// for (int i = 0; i < w*h; ++i)
	// {
	// 	cb[i]=0;
	// }
	sum=0;
}
Chessboard::~Chessboard()
{
	delete [] cb;
}
bool Chessboard::SetChessPoint(const ChessPoint& cp,int id)
{
	if(!isPointValid(cp))
	{
		return false;
	}

	//if (GetIdOfPoint(cp)!=0)
	//{
	//	return false;
	//}
	if (GetIdOfPoint(cp)==0)
	{
		sum++;
	}
	cb[cp.y*width+cp.x]=id;

	return true;
}
int Chessboard::GetIdOfPoint(const ChessPoint& cp)const
{
	if (isPointValid(cp))
	{
		return cb[cp.y*width+cp.x];
	}
	return -1;
}


bool Chessboard::isPointValid(const ChessPoint& cp)const
{
	if (cp.x<0||cp.x>=width||cp.y<0||cp.y>=height)
	{
		return false;
	}
	return true;
}
