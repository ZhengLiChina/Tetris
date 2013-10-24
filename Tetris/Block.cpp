#include"Block.h"
#include<algorithm>

Block::Block(Chessboard* cb):chessboard(cb)
{
	//Init(1);
	shapeKinds=7;
}

Block::Block(int shape)
{
	//Init(1);
	SetBlock(shape);
	chessboard=NULL;
	shapeKinds=7;
}


Block::~Block()
{
}

Block::iterator Block::begin()
{
	return block.begin();
}

Block::iterator Block::end()
{
	return block.end();
}

bool Block::Init(int shape)
{
	position=CP(3,0);

	SetBlock(shape);
	bool result=true;
	for(auto i=block.begin();i!=block.end();i++)
	{
		result&=NoCollide(position+*i);
		if (!result)
		{
			return false;
		}
	}

	//for(auto i=block.begin();i!=block.end();i++)
	//{
	//	chessboard.SetChessPoint(*i+position,color);
	//}
	return true;
}

bool Block::Move(ChessPoint dir)
{
	bool result=true;
	for(auto i=block.begin();i!=block.end();i++)
	{
		//ascertain the shape's edge of the moving direction
		//if (std::find(block.begin(),block.end(), (*i+dir))==block.end())
		//{
		result&=NoCollide(position+*i+dir);
		//}
	}
	if (result)
	{
		//for(auto i=block.begin();i!=block.end();i++)
		//{
		//	chessboard.SetChessPoint(*i+position,0);
		//}
		position=position+dir;
		//for(auto i=block.begin();i!=block.end();i++)
		//{
		//	chessboard.SetChessPoint(position+*i,color);
		//}
	}

	return result;
}
bool Block::Rotate()
{
	auto temp(block);
	bool result=true;
	for(auto i=temp.begin();i!=temp.end();i++)
	{
		int tempx=i->x;
		int tempy=i->y;

		i->x=tempy;
		i->y=-tempx+offside;
		result&=NoCollide(CP(i->x+position.x,i->y+position.y));
	}

	if (result)
	{
		block=temp;
	}
	return true;
}

bool Block::NoCollide(CP cp)
{
	return (!chessboard->GetIdOfPoint(cp));
}

bool Block::SetBlock(int shape)
{
	block.clear();
	ChessPoint cp[]=
	{
		CP(0,0),CP(0,1),CP(1,0),CP(1,1)
	};
	int len=4;
	//color=shape+1;
	color=1;
	switch (shape)
	{
	case 0://Ìï
		offside=1;
		break;
	case 1://T
		cp[2]=CP(0,2);
		offside=2;
		break;
	case 2:// ----
		cp[2]=CP(0,2);
		cp[3]=CP(0,3);
		offside=3;
		break;
	case 3://L
		cp[3]=CP(0,2);
		offside=2;
		break;
	case 4://oppsite L
		cp[2]=CP(0,2);
		cp[3]=CP(1,2);
		offside=2;
		break;
	case 5://Z
		cp[2]=CP(1,2);
		offside=2;
		break;
	case 6://oppsite Z
		cp[0]=CP(0,2);
		offside=2;
		break;
	default:
		break;
	}

	for (int i = 0; i < len; i++)
	{
		block.push_back(cp[i]);
	}
	return true;
}
