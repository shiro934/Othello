#include "TitleScene.h"

#include "WindowInfo.h"
#include "DxLib.h"


#define STRING_COLOR 0x00ffff	//文字の色
#define MAX_FRAME_COUNT 110
#define FLASH_TIMING 70		//点滅するタイミング

TitleScene::TitleScene()
{
	frameCount = 0;
}


TitleScene::~TitleScene()
{
}

void TitleScene::input(const InputKey& key, const InputMouse& mouse) {
	//次のシーンへ遷移するフラグを立てる
	if (key.checkKeyState(KEY_INPUT_RETURN) == KEY_DOWN) {
		nextSceneFlag = true;
	}

	if (mouse.getMouseState(MOUSE_INPUT_LEFT) == BUTTON_DOWN) {
		nextSceneFlag = true;
	}
}

void TitleScene::update() {
	frameCount++;

	//frameCountがintの範囲内に収まるように
	if (frameCount == INT_MAX - 1) {
		frameCount = 0;
	}
}

void TitleScene::render() const {
	//タイトルの表示
	DrawString(WND_WIDTH / 2, WND_HEIGHT / 3, "オセロ", STRING_COLOR);

	//文字列を点滅させて表示
	if (frameCount % MAX_FRAME_COUNT < FLASH_TIMING) {
		DrawString(WND_WIDTH / 3 + 90, WND_HEIGHT * 2 / 3, "PUSH ENTER TO START", STRING_COLOR);
	}
}

SceneType TitleScene::nextSceneType() const {
	return GAME;
}