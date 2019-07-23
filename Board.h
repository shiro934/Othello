#pragma once
#ifndef INCLUDED_BOARD_H_
#define INCLUDED_BOARD_H_

#include "BoardInfo.h"
#include "BoardCellType.h"

class Board
{
public:
	Board(const int boardPosX, const int boardPosY, const int playerNum);
	~Board();

	bool isCursorOnBoard(const int posX, const int posY) const;
	bool canTurnPlayerPutedStone(const unsigned int turnPlayer) const;

	bool putStone(const int x, const int y, const unsigned int turnPlayer);
	void turnOver(const int x, const int y, const unsigned int turnPlayer);

	void render(const int x, const int y) const;

	void getStoneNum(unsigned int stone[]) const {
		for (int i = 0; i < PLAYER_NUM; i++) {
			stone[i] = *(stoneNum + i);
		}
	}
private : 
	void boardInit();

	void drawBoard(const int x, const int y) const;
	void drawStone() const;
	BoardCellType board[BOARD_LINE_CELL_NUM][BOARD_ROW_CELL_NUM];
	const int BOARD_POS_X, BOARD_POS_Y;
	const int PLAYER_NUM;
	unsigned int* stoneNum;	//ƒvƒŒƒCƒ„[‚²‚Æ‚ÌÎ‚Ì”
};

#endif // !INCLUDED_BOARD_H_
