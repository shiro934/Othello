#include "GameScene.h"

#include "DxLib.h"

#include "WindowInfo.h"

#include <cassert>

#define BOARD_POS_X (WND_WIDTH / 3 - 50)
#define BOARD_POS_Y WND_HEIGHT / 5



GameScene::GameScene()
{
	gameOverFlag = false;
	turnPlayerNum = 0;
	boardInit();
}


GameScene::~GameScene()
{
}

void GameScene::boardInit() {
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

	playerStoneNum[0] = 2;
	playerStoneNum[1] = 2;
}

bool GameScene::isGameOver() {
	return false;
}

bool GameScene::isCursorOnBoard() const {
	//盤上にカーソルがあるかをチェック
	if ((mousePosX < BOARD_POS_X) || (mousePosX > BOARD_POS_X + BOARD_WIDTH)) {
		return false;
	}
	if ((mousePosY < BOARD_POS_Y) || (mousePosY > BOARD_POS_Y + BOARD_HEIGHT)) {
		return false;
	}

	return true;
}

void GameScene::playerSwitching() {
	if (turnPlayerNum == PLAYER_NUM - 1) {
		turnPlayerNum = 0;
	}
	else {
		turnPlayerNum++;
	}
}

void GameScene::input(const InputKey& key, const InputMouse& mouse) {
	//シーンを切り替え
	if (key.checkKeyState(KEY_INPUT_RETURN) == KEY_DOWN) {
		nextSceneFlag = true;
	}
	mouse.getMousePos(mousePosX, mousePosY);

	//カーソルが指すマス
	cellX = (mousePosX - BOARD_POS_X) / BOARD_CELL_SIZE;
	cellY = (mousePosY - BOARD_POS_Y) / BOARD_CELL_SIZE;

	if (mouse.getMouseState(MOUSE_INPUT_LEFT) == BUTTON_DOWN) {
		if (putStone()) {
			playerSwitching();
		}
	}
}

void GameScene::update() {
	if (gameOverFlag) {
		return;
	}
}

void GameScene::render() const {
	//盤の描画
	drawBoard();

	//盤上の石の描画
	drawStone();

	textRender();
}

//盤に石を置く
bool GameScene::putStone() {
	if (isCursorOnBoard() == false) {
		return false;
	}

	assert(cellX >= 0 && cellX <= BOARD_ROW_CELL_NUM);
	assert(cellY >= 0 && cellY <= BOARD_LINE_CELL_NUM);

	//カーソルのあるマスに何か置いてあるかチェック
	if (board[cellY][cellX] != BoardCellType::EMPTY) {
		return false;
	}
	if (isPutedStone() == false) {
		return false;
	}

	board[cellY][cellX] = static_cast<BoardCellType>(turnPlayerNum);
	return true;
}

bool GameScene::isPutedStone() {
	BoardCellType type = static_cast<BoardCellType>(turnPlayerNum);
	bool flag = false;
	if (leftTurnOverCheck()) {
		for (int i = cellX - 1; board[cellY][i] != type; i--) {
			playerStoneNum[board[cellY][i]]--;
			board[cellY][i] = type;
			playerStoneNum[turnPlayerNum]++;
		}
		flag = true;
	}
	if (rightTurnOverCheck()) {
		for (int i = cellX + 1; board[cellY][i] != type; i++) {
			playerStoneNum[board[cellY][i]]--;
			board[cellY][i] = type;
			playerStoneNum[turnPlayerNum]++;
		}
		flag = true;
	}
	if (topTurnOverCheck()) {
		for (int i = cellY - 1; board[i][cellX] != type; i--) {
			playerStoneNum[board[i][cellX]]--;
			board[i][cellX] = type;
			playerStoneNum[turnPlayerNum]++;
		}
		flag = true;
	}
	if (underTurnOverCheck()) {
		for (int i = cellY + 1; board[i][cellX] != type; i++) {
			playerStoneNum[board[i][cellX]]--;
			board[i][cellX] = type;
			playerStoneNum[turnPlayerNum]++;
		}
		flag = true;
	}
	if (top_leftTurnOverCheck()) {
		for (int i = cellY - 1, j = cellX - 1; board[i][j] != type; i--, j--) {
			playerStoneNum[board[i][j]]--;
			board[i][j] = type;
			playerStoneNum[turnPlayerNum]++;
		}
		flag = true;
	}
	if (top_rightTurnOverCheck()) {
		for (int i = cellY - 1, j = cellX + 1; board[i][j] != type; i--, j++) {
			playerStoneNum[board[i][j]]--;
			board[i][j] = type;
			playerStoneNum[turnPlayerNum]++;
		}
		flag = true;
	}
	if (under_leftTurnOverCheck()) {
		for (int i = cellY + 1, j = cellX - 1; board[i][j] != type; i++, j--) {
			playerStoneNum[board[i][j]]--;
			board[i][j] = type;
			playerStoneNum[turnPlayerNum]++;
		}
		flag = true;
	}
	if (under_rightTurnOverCheck()) {
		for (int i = cellY + 1, j = cellX + 1; board[i][j] != type; i++, j++) {
			playerStoneNum[board[i][j]]--;
			board[i][j] = type;
			playerStoneNum[turnPlayerNum]++;
		}
		flag = true;
	}

	if (flag) {
		playerStoneNum[turnPlayerNum]++;
	}
	return flag;
}

bool GameScene::leftTurnOverCheck() const {
	int i = cellX - 1;
	BoardCellType type = static_cast<BoardCellType>(turnPlayerNum);

	if (board[cellY][i] == BoardCellType::EMPTY) {
		return false;
	}
	if (board[cellY][i] == type) {
		return false;
	}
	i--;
	while (i >= 0) {
		if (board[cellY][i] == BoardCellType::EMPTY) {
			break;
		}
		if (board[cellY][i] == type) {
			return true;
		}
		i--;
	}
	return false;
}

bool GameScene::rightTurnOverCheck() const {
	int i = cellX + 1;
	BoardCellType type = static_cast<BoardCellType>(turnPlayerNum);

	if (board[cellY][i] == BoardCellType::EMPTY) {
		return false;
	}
	if (board[cellY][i] == type) {
		return false;
	}
	i++;
	while (i <= BOARD_ROW_CELL_NUM) {
		if (board[cellY][i] == BoardCellType::EMPTY) {
			break;
		}
		if (board[cellY][i] == type) {
			return true;
		}
		i++;
	}
	return false;
}

bool GameScene::topTurnOverCheck() const {
	int i = cellY - 1;
	BoardCellType type = static_cast<BoardCellType>(turnPlayerNum);

	if (board[i][cellX] == BoardCellType::EMPTY) {
		return false;
	}
	if (board[i][cellX] == type) {
		return false;
	}
	i--;
	while (i >= 0) {
		if (board[i][cellX] == BoardCellType::EMPTY) {
			break;
		}
		if (board[i][cellX] == type) {
			return true;
		}
		i--;
	}
	return false;
}

bool GameScene::underTurnOverCheck() const {
	int i = cellY + 1;
	BoardCellType type = static_cast<BoardCellType>(turnPlayerNum);

	if (board[i][cellX] == BoardCellType::EMPTY) {
		return false;
	}
	if (board[i][cellX] == type) {
		return false;
	}
	i++;
	while (i <= BOARD_LINE_CELL_NUM) {
		if (board[i][cellX] == BoardCellType::EMPTY) {
			break;
		}
		if (board[i][cellX] == type) {
			return true;
		}
		i++;
	}
	return false;
}

bool GameScene::top_leftTurnOverCheck() const {
	int i = cellY - 1;
	int j = cellX - 1;
	BoardCellType type = static_cast<BoardCellType>(turnPlayerNum);

	if (board[i][j] == BoardCellType::EMPTY) {
		return false;
	}
	if (board[i][j] == type) {
		return false;
	}
	i--;
	j--;
	while (i >= 0 && j >= 0) {
		if (board[i][j] == BoardCellType::EMPTY) {
			break;
		}
		if (board[i][j] == type) {
			return true;
		}
		i--;
		j--;
	}
	return false;
}

bool GameScene::top_rightTurnOverCheck() const {
	int i = cellY - 1;
	int j = cellX + 1;
	BoardCellType type = static_cast<BoardCellType>(turnPlayerNum);

	if (board[i][j] == BoardCellType::EMPTY) {
		return false;
	}
	if (board[i][j] == type) {
		return false;
	}
	i--;
	j++;
	while (i >= 0 && j <= BOARD_ROW_CELL_NUM) {
		if (board[i][j] == BoardCellType::EMPTY) {
			break;
		}
		if (board[i][j] == type) {
			return true;
		}
		i--;
		j++;
	}
	return false;
}

bool GameScene::under_leftTurnOverCheck() const {
	int i = cellY + 1;
	int j = cellX - 1;
	BoardCellType type = static_cast<BoardCellType>(turnPlayerNum);

	if (board[i][j] == BoardCellType::EMPTY) {
		return false;
	}
	if (board[i][j] == type) {
		return false;
	}
	i++;
	j--;
	while (i <= BOARD_LINE_CELL_NUM && j >= 0) {
		if (board[i][j] == BoardCellType::EMPTY) {
			break;
		}
		if (board[i][j] == type) {
			return true;
		}
		i++;
		j--;
	}
	return false;
}

bool GameScene::under_rightTurnOverCheck() const {
	int i = cellY + 1;
	int j = cellX + 1;
	BoardCellType type = static_cast<BoardCellType>(turnPlayerNum);

	if (board[i][j] == BoardCellType::EMPTY) {
		return false;
	}
	if (board[i][j] == type) {
		return false;
	}
	i++;
	j++;
	while (i <= BOARD_LINE_CELL_NUM && j <= BOARD_ROW_CELL_NUM) {
		if (board[i][j] == BoardCellType::EMPTY) {
			break;
		}
		if (board[i][j] == type) {
			return true;
		}
		i++;
		j++;
	}
	return false;
}
void GameScene::drawBoard() const {
	//盤の下地を描画
	DrawBox(BOARD_POS_X, BOARD_POS_Y
		, BOARD_POS_X + BOARD_WIDTH, BOARD_POS_Y + BOARD_HEIGHT, BOARD_COLOR, TRUE);

	//マウスが指しているマスを光らせる
	if (isCursorOnBoard()) {
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

void GameScene::drawStone() const {
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

void GameScene::textRender() const {
	/* 文字の描画 */
	if (gameOverFlag) {
		DrawString(WND_WIDTH / 2, WND_HEIGHT / 2, "GAME OVER", 0xff0000);
	}
	DrawFormatString(0, 30, 0xffffff, "マウスカーソルの位置 : (%d, %d)"
					, mousePosX, mousePosY);
	DrawFormatString(0, 60, 0xffffff, "マスの位置 : (%d, %d)", cellX, cellY);

	DrawFormatString(0, 90, 0xffffff, "黒の数 : %d", playerStoneNum[0]);
	DrawFormatString(0, 120, 0xffffff, "白の数 : %d", playerStoneNum[1]);

	if (turnPlayerNum == 0) {
		DrawString(WND_WIDTH / 2 - 30, 50, "黒の手番です", 0xffffff);
	}
	else {
		DrawString(WND_WIDTH / 2 - 30, 50, "白の手番です", 0xffffff);
	}
}

SceneType GameScene::nextSceneType() const {
	return TITLE;
}
