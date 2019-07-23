#pragma once
#ifndef INCLUDED_BOARD_CHECK_H_
#define INCLUDED_BOARD_CHECK_H_

#include "BoardCellType.h"
#include "BoardInfo.h"

class BoardCheck
{
public:
	static bool canTurnPlayerPutedStone(const BoardCellType board[BOARD_LINE_CELL_NUM][BOARD_ROW_CELL_NUM], const unsigned int turnPlayer);
	static bool canPutedStone(const BoardCellType board[BOARD_LINE_CELL_NUM][BOARD_ROW_CELL_NUM], 
		const int x, const int y, const unsigned int turnPlayer);
	static bool turnOverCheck(const BoardCellType board[BOARD_LINE_CELL_NUM][BOARD_ROW_CELL_NUM], 
		const int x, const int y, const unsigned int turnPlayer, const int horizontal, const int vertical);
	static bool isCellOnBoard(const int x, const int y);
private : 
	BoardCheck();
	~BoardCheck();
};

#endif // !INCLUDED_BOARD_CHECK_H_
