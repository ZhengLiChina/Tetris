#include"ChessPoint.h"

ChessPoint operator+(const ChessPoint& l,const ChessPoint& r)
{
	return ChessPoint(l.x+r.x,l.y+r.y);
}

ChessPoint operator-(const ChessPoint& l,const ChessPoint& r)
{
	return ChessPoint(l.x-r.x,l.y-r.y);
}

bool operator==(const ChessPoint& l,const ChessPoint& r)
{
	return l.x==r.x&&l.y==r.y;
}