#ifndef GAMERULER_ZHENGLI
#define GAMERULER_ZHENGLI

#include"ChessPoint.h"
#include"Chessboard.h"
#include"Block.h"

enum Result {Win,Lose,Check,ToBeContinued,Error };


class GameRuler
{
public:
	GameRuler(Chessboard& cb,Block& block);
	~GameRuler();
	Result Go(ChessPoint direction);
	bool ResetBlock();
	bool Rotate();
	int GetNextShape(){return nextShape;}
	int GetLinesKilled(){return linesKilled;}

private:
	int score;
	int linesKilled;
	int* lines;
	Chessboard& chessboard;
	Block& block;
	ChessPoint InitBlock();
	bool KillLine(int line);
	bool Drop();

	int currentShape;
	int nextShape;
};



#endif