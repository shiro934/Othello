#include "DxLib.h"

#include "WindowInfo.h"
#include "Resident.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow) {
	ChangeWindowMode(TRUE);
	SetGraphMode(WND_WIDTH, WND_HEIGHT, 32);

	if (DxLib_Init() == -1) {
		MessageBox(nullptr, "DX���C�u�������������ł��܂���ł���", 
			"�G���[���b�Z�[�W", MB_OK);
		return -1;
	}

	Resident resident;

	while (true) {
		//�E�C���h�E���b�Z�[�W������
		if (ProcessMessage() != 0) {
			break;
		}

		//���͏�Ԃ��Z�b�g
		resident.inputKey.setKey();	//���݂̃L�[���͏�Ԃ��Z�b�g
		resident.inputMouse.setMouseState();  //���݂̃}�E�X�̏�Ԃ��Z�b�g

		ClearDrawScreen();	//��ʂ̊G���폜

							//�V�[������
		resident.sceneManag.sceneChange();
		resident.sceneManag.input(resident.inputKey, resident.inputMouse);
		resident.sceneManag.update();
		resident.sceneManag.render();

		//fps����
		resident.fpsCalc.update();
		resident.fpsCalc.drawFPS();
		resident.fpsCalc.wait();
	}

	DxLib_End();

	return 0;
}