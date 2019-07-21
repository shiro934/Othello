#include "DxLib.h"

#include "WindowInfo.h"
#include "Resident.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow) {
	ChangeWindowMode(TRUE);
	SetGraphMode(WND_WIDTH, WND_HEIGHT, 32);

	if (DxLib_Init() == -1) {
		MessageBox(nullptr, "DXライブラリが初期化できませんでした", 
			"エラーメッセージ", MB_OK);
		return -1;
	}

	Resident resident;

	while (true) {
		//ウインドウメッセージを処理
		if (ProcessMessage() != 0) {
			break;
		}

		//入力状態をセット
		resident.inputKey.setKey();	//現在のキー入力状態をセット
		resident.inputMouse.setMouseState();  //現在のマウスの状態をセット

		ClearDrawScreen();	//画面の絵を削除

							//シーン処理
		resident.sceneManag.sceneChange();
		resident.sceneManag.input(resident.inputKey, resident.inputMouse);
		resident.sceneManag.update();
		resident.sceneManag.render();

		//fps処理
		resident.fpsCalc.update();
		resident.fpsCalc.drawFPS();
		resident.fpsCalc.wait();
	}

	DxLib_End();

	return 0;
}