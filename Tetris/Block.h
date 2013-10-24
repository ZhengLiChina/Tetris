#ifndef BLOCK_ZHENGLI
#define BLOCK_ZHENGLI


#include<vector>
#include"Chessboard.h"
class Block
{
public:
	Block(Chessboard* cb);
	Block(int shape);
	~Block();

	typedef std::vector<ChessPoint>::iterator iterator;

	iterator begin();
	iterator end();

	bool Init(int shape);

	bool Move(ChessPoint dir);
	bool Rotate();
	CP GetPosition(){return position;}
	int GetColor(){return color;}
	int GetKindsNum(){return shapeKinds;}

private:
	std::vector<ChessPoint> block;
	Chessboard* chessboard;
	ChessPoint position;
	int color;
	int offside;// max |x| |y|, rotate uses it
	int shapeKinds;

	bool NoCollide(CP cp);
	bool SetBlock(int shape);
};

#endif