#include "Board.h"

#include "BoardCheck.h"

#include "DxLib.h"

#include <cassert>

Board::Board(const int boardPosX, const int boardPosY, const int playerNum)
	: BOARD_POS_X(boardPosX), BOARD_POS_Y(boardPosY), PLAYER_NUM(playerNum)
{
	stoneNum = new unsigned int[PLAYER_NUM];
	boardInit();
}


Board::~Board()
{
	delete[] stoneNum;
}

void Board::boardInit() {
	//盤面の初期化
	for (int i = 0; i < BOARD_LINE_CELL_NUM; i++) {
		for (int j = 0; j < BOARD_ROW_CELL_NUM; j++) {
			board[i][j] = BoardCellType::EMPTY;
		}
	}
	//石の初期配置
	board[BOARD_LINE_CELL_NUM / 2 - 1][BOARD_ROW_CELL_NUM / 2 - 1] = BoardCellType::LOCATED_BLACK_STONE;
	board[BOARD_LINE_CELL_NUM / 2][BOARD_ROW_CELL_NUM / 2 - 1] = BoardCellType::LOCATED_WHITE_STONE;
	board[BOARD_LINE_CELL_NUM / 2 - 1][BOARD_ROW_CELL_NUM / 2] = BoardCellType::LOCATED_WHITE_STONE;
	board[BOARD_LINE_CELL_NUM / 2][BOARD_ROW_CELL_NUM / 2] = BoardCellType::LOCATED_BLACK_STONE;

	stoneNum[0] = 2;
	stoneNum[1] = 2;
}

bool Board::canTurnPlayerPutedStone(const unsigned int turnPlayer) const {
	return BoardCheck::canTurnPlayerPutedStone(board, turnPlayer);
}

bool Board::isCursorOnBoard(const int posX, const int posY) const {
	//盤上にカーソルがあるかをチェック
	if ((posX < BOARD_POS_X) || (posX > BOARD_POS_X + BOARD_WIDTH)) {
		return false;
	}
	if ((posY < BOARD_POS_Y) || (posY > BOARD_POS_Y + BOARD_HEIGHT)) {
		return false;
	}

	return true;
}

bool Board::putStone(const int x, const int y, const unsigned int turnPlayer) {
	assert(x >= 0 && x < BOARD_ROW_CELL_NUM);
	assert(y >= 0 && y < BOARD_LINE_CELL_NUM);

	//カーソルのあるマスに何か置いてあるかチェック
	if (board[y][x] != BoardCellType::EMPTY) {
		return false;
	}
	if (BoardCheck::canPutedStone(board, x, y, turnPlayer) == false) {
		return false;
	}

	turnOver(x, y, turnPlayer);
	board[y][x] = static_cast<BoardCellType>(turnPlayer);
	return true;
}

void Board::turnOver(const int x, const int y, const unsigned int turnPlayer) {
	BoardCellType type = static_cast<BoardCellType>(turnPlayer);
	for (int vertical = -1; vertical <= 1; vertical++) {
		for (int horizontal = -1; horizontal <= 1; horizontal++) {
			if (BoardCheck::turnOverCheck(board, x, y, turnPlayer, horizontal, vertical)) {
				for (int i = y + vertical, j = x + horizontal; board[i][j] != type; i+= vertical, j += horizontal) {
					stoneNum[board[i][j]]--;
					board[i][j] = type;
					stoneNum[turnPlayer]++;
				}
			}
		}
	}

	stoneNum[turnPlayer]++;
}

void Board::render(const int x, const int y) const {
	drawBoard(x, y);
	drawStone();
}

void Board::drawBoard(const int x, const int y) const {
	int cellX = (x - BOARD_POS_X) / BOARD_CELL_SIZE;
	int cellY = (y - BOARD_POS_Y) / BOARD_CELL_SIZE;
	//盤の下地を描画
	DrawBox(BOARD_POS_X, BOARD_POS_Y
		, BOARD_POS_X + BOARD_WIDTH, BOARD_POS_Y + BOARD_HEIGHT, BOARD_COLOR, TRUE);

	//マウスが指しているマスを光らせる
	if (isCursorOnBoard(x, y)) {
		DrawBox(BOARD_POS_X + (BOARD_CELL_SIZE * cellX), BOARD_POS_Y + (BOARD_CELL_SIZE * cellY)
			, BOARD_POS_X + (BOARD_CELL_SIZE * (cellX + 1)), BOARD_POS_Y + (BOARD_CELL_SIZE * (cellY + 1)), 0x00ffff, TRUE);
	}

	//グリッド線描画
	for (int i = 0; i < BOARD_LINE_CELL_NUM; i++) {
		DrawLine(BOARD_POS_X, BOARD_POS_Y + BOARD_CELL_SIZE * i,
			BOARD_POS_X + BOARD_WIDTH, BOARD_POS_Y + BOARD_CELL_SIZE * i
			, 0x000000, BOARD_GRID_TICKNESS);
	}
	for (int j = 0; j < BOARD_ROW_CELL_NUM; j++) {
		DrawLine(BOARD_POS_X + BOARD_CELL_SIZE * j, BOARD_POS_Y,
			BOARD_POS_X + BOARD_CELL_SIZE * j, BOARD_POS_Y + BOARD_HEIGHT
			, 0x000000, BOARD_GRID_TICKNESS);
	}
}

void Board::drawStone() const {
	//盤上の石を描画
	for (int i = 0; i < BOARD_LINE_CELL_NUM; i++) {
		for (int j = 0; j < BOARD_ROW_CELL_NUM; j++) {
			if (board[i][j] != BoardCellType::EMPTY) {
				assert(board[i][j] != BoardCellType::STONE_MAX);
				DrawCircle(BOARD_POS_X + (BOARD_CELL_SIZE * j) + BOARD_CELL_SIZE / 2,
					BOARD_POS_Y + (BOARD_CELL_SIZE * i) + BOARD_CELL_SIZE / 2,
					BOARD_CELL_SIZE / 2 - 5,
					stoneColor[board[i][j]], TRUE);
			}
		}
	}
}