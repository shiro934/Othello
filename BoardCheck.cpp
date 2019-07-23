#include "BoardCheck.h"



BoardCheck::BoardCheck()
{
}


BoardCheck::~BoardCheck()
{
}

bool BoardCheck::canTurnPlayerPutedStone(const BoardCellType board[BOARD_LINE_CELL_NUM][BOARD_ROW_CELL_NUM], const unsigned int turnPlayer) {
	for (int i = 0; i < BOARD_LINE_CELL_NUM; i++) {
		for (int j = 0; j < BOARD_ROW_CELL_NUM; j++) {
			if (board[i][j] != BoardCellType::EMPTY) {
				continue;
			}
			if (canPutedStone(board, j, i, turnPlayer)) {
				return true;
			}
		}
	}
	return false;
}

bool BoardCheck::canPutedStone(const BoardCellType board[BOARD_LINE_CELL_NUM][BOARD_ROW_CELL_NUM], const int x, const int y, const unsigned int turnPlayer) {
	//上下左右ななめをチェックして、石が置けるかを調べる
	for (int vertical = -1; vertical <= 1; vertical++) {
		for (int horizontal = -1; horizontal <= 1; horizontal++) {
			if (turnOverCheck(board, x, y, turnPlayer, horizontal, vertical)) {
				return true;
			}
		}
	}
	return false;
}

bool BoardCheck::turnOverCheck(const BoardCellType board[BOARD_LINE_CELL_NUM][BOARD_ROW_CELL_NUM]
	, const int x, const int y, const unsigned int turnPlayer, const int horizontal, const int vertical) {
	int i = y + vertical;
	int j = x + horizontal;

	BoardCellType type = static_cast<BoardCellType>(turnPlayer);

	if (board[i][j] == BoardCellType::EMPTY) {
		return false;
	}
	if (board[i][j] == type) {
		return false;
	}
	i += vertical;
	j += horizontal;

	while (isCellOnBoard(j, i)) {
		if (board[i][j] == BoardCellType::EMPTY) {
			break;
		}
		if (board[i][j] == type) {
			return true;
		}
		i += vertical;
		j += horizontal;
	}
	return false;
}

bool BoardCheck::isCellOnBoard(const int x, const int y) {
	if (x < 0 || x > BOARD_ROW_CELL_NUM - 1) {
		return false;
	}
	if (y < 0 || y > BOARD_LINE_CELL_NUM - 1) {
		return false;
	}
	return true;
}