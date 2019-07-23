#pragma once
#ifndef INCLUDED_GAME_SCENE_H_
#define INCLUDED_GAME_SCENE_H_

#include "Scene.h"

#include "BoardCellType.h"
#include "BoardInfo.h"

#include "Board.h"

#define PLAYER_NUM 2

class GameScene :
	public Scene
{
public:
	GameScene();
	~GameScene();

	void input(const InputKey& key, const InputMouse& mouse) override;
	void update() override;
	void render() const override;
	SceneType nextSceneType() const override;

private :
	void textRender() const;
	

	void playerSwitching();
	bool isGameFinished();

	bool gameFinishFlag;

	Board* board;
	int mousePosX, mousePosY;
	int cellX, cellY;	//�{�[�h�̃}�X�̈ʒu

	int turnPlayerNum;	//��Ԃ̃v���C���[�ԍ�
	int passNum = 0;		//�A���p�X��
	bool isTurnPlayerPutedCheck;	//��Ԃ̃v���C���[���΂�u���邩���L�����Ă���

	bool turnSwitchFlag = true;	//true�Ȃ�΂�u���Ǝ�Ԃ��ς��
};


#endif // !INCLUDED_GAME_SCENE_H_

