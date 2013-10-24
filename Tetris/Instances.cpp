#include"Instances.h"


Chessboard& GetChessboard()
{
	static Chessboard cb(MapWidth,MapHeight);
	return cb;
}
Block& GetBlock()
{
	static Block block(&GetChessboard());
	return block;
}

GameRuler& GetGameRuler()
{
	static GameRuler gr(GetChessboard(),GetBlock());
	return gr;
}