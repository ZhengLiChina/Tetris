#include"GameRuler.h"
#include"GlobalDefinition.h"
#include<ctime>

GameRuler::GameRuler(Chessboard& cb,Block& block):chessboard(cb),block(block)
{
	lines=new int [MapHeight];
	memset(lines,0,MapHeight*sizeof(int));
	srand(time(0));
	currentShape=rand()%block.GetKindsNum();
	nextShape=rand()%block.GetKindsNum();
	block.Init(currentShape);
}

GameRuler::~GameRuler()
{
	delete [] lines;
}

Result GameRuler::Go(ChessPoint dir)
{
	bool result=block.Move(dir);
	if (dir==CP(Direction::Down))
	{
		if (!result)//Cannot move, Check
		{
			for(auto i=block.begin();i!=block.end();i++)
			{
				chessboard.SetChessPoint(block.GetPosition()+*i,block.GetColor());
			}
			for(auto i=block.begin();i!=block.end();i++)
			{
				int n=(*i+block.GetPosition()).y;
				lines[n]++;
				if (lines[n]==MapWidth)
				{
					KillLine(n);
				}
			}
			Drop();
			if(!ResetBlock())
			{
				return Result::Lose;
			}
			return Result::Check;
		}
	}

	return Result::ToBeContinued;
}


bool GameRuler::KillLine(int line)
{
	linesKilled++;
	lines[line]=0;
	for (int i = 0; i < MapWidth; i++)
	{
		chessboard.SetChessPoint(CP(i,line),0);
	}

	return true;
}

bool GameRuler::Drop()
{
	int distance=1;//distance between two non-empty lines
	for (int i = MapHeight-1; i > distance-1; i--)
	{
		if (lines[i]==0)
		{
			while (lines[i-distance]==0)
			{
				distance++;
				if (i-distance==0)//above is all empty
				{
					return true;
				}
			}
			lines[i]=lines[i-distance];
			lines[i-distance]=0;
			for (int j = 0; j < MapWidth; j++)
			{
				chessboard.SetChessPoint(CP(j,i),chessboard.GetIdOfPoint(CP(j,i-distance)));
				chessboard.SetChessPoint(CP(j,i-distance),0);//clear that line, because we may break the loop before it is overridden.
			}
		}
	}
	return true;
}


bool GameRuler::ResetBlock()
{
	currentShape=nextShape;
	nextShape=rand()%block.GetKindsNum();
	return block.Init(currentShape);
}

bool GameRuler::Rotate()
{
	return block.Rotate();
}