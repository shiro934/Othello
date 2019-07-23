#include "GameScene.h"

#include "DxLib.h"

#include "WindowInfo.h"

#include <cassert>

#define BOARD_POS_X (WND_WIDTH / 3 - 50)
#define BOARD_POS_Y WND_HEIGHT / 5

GameScene::GameScene()
{
	board = new Board(BOARD_POS_X, BOARD_POS_Y, PLAYER_NUM);
	gameFinishFlag = false;
	turnPlayerNum = 0;

	isTurnPlayerPutedCheck = board->canTurnPlayerPutedStone(turnPlayerNum);
}


GameScene::~GameScene()
{
}

bool GameScene::isGameFinished() {
	return false;
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
	if (key.checkKeyState(KEY_INPUT_S) == KEY_DOWN) {
		turnSwitchFlag = !turnSwitchFlag;
	}

	mouse.getMousePos(mousePosX, mousePosY);

	//カーソルが指すマス
	cellX = (mousePosX - BOARD_POS_X) / BOARD_CELL_SIZE;
	cellY = (mousePosY - BOARD_POS_Y) / BOARD_CELL_SIZE;

	if (mouse.getMouseState(MOUSE_INPUT_LEFT) == BUTTON_DOWN) {
		if (isTurnPlayerPutedCheck) {
			if (board->isCursorOnBoard(mousePosX, mousePosY)) {
				if (board->putStone(cellX, cellY, turnPlayerNum)) {
					if (turnSwitchFlag) {
						playerSwitching();
					}
					passNum = 0;
					isTurnPlayerPutedCheck = board->canTurnPlayerPutedStone(turnPlayerNum);
					if (isTurnPlayerPutedCheck == false) {
						passNum++;
					}
				}
			}
		}
		else {
			if (passNum == PLAYER_NUM) {
				gameFinishFlag = true;
				return;
			}
			if (turnSwitchFlag) {
				playerSwitching();
				isTurnPlayerPutedCheck = board->canTurnPlayerPutedStone(turnPlayerNum);
				if (isTurnPlayerPutedCheck == false) {
					passNum++;
				}
			}
		}
	}
}

void GameScene::update() {
	if (gameFinishFlag) {
		return;
	}
}

void GameScene::render() const {
	board->render(mousePosX, mousePosY);
	textRender();
}

void GameScene::textRender() const {
	/* 文字の描画 */
	DrawFormatString(0, 30, 0xffffff, "マウスカーソルの位置 : (%d, %d)"
					, mousePosX, mousePosY);
	DrawFormatString(0, 60, 0xffffff, "マスの位置 : (%d, %d)", cellX, cellY);

	unsigned int playerStoneNum[PLAYER_NUM];
	board->getStoneNum(playerStoneNum);

	DrawFormatString(0, 90, 0xffffff, "黒の数 : %d", playerStoneNum[0]);
	DrawFormatString(0, 120, 0xffffff, "白の数 : %d", playerStoneNum[1]);
	if (turnSwitchFlag) {
		DrawString(0, 150, "手番が変わる", 0xffffff);
	}
	else {
		DrawString(0, 150, "手番が変わらない", 0xffffff);
	}
	DrawString(0, 170, "切り替えキー : s", 0xffffff);

	if (gameFinishFlag) {
		if (playerStoneNum[0] > playerStoneNum[1]) {
			DrawString(WND_WIDTH / 2 - 30, 50, "黒の勝ちです", 0xffffff);
		} else 	if (playerStoneNum[0] < playerStoneNum[1]) {
			DrawString(WND_WIDTH / 2 - 30, 50, "白の勝ちです", 0xffffff);
		}
		else {
			DrawString(WND_WIDTH / 2 - 30, 50, "引き分けです", 0xffffff);
		}
	}
	else {
		if (turnPlayerNum == 0) {
			DrawString(WND_WIDTH / 2 - 30, 50, "黒の手番です", 0xffffff);
		}
		else {
			DrawString(WND_WIDTH / 2 - 30, 50, "白の手番です", 0xffffff);
		}
		if (isTurnPlayerPutedCheck == false) {
			DrawString(WND_WIDTH / 2 - 30, 80, "置ける場所がないのでパスです", 0xffffff);
		}
	}
}

SceneType GameScene::nextSceneType() const {
	return TITLE;
}
