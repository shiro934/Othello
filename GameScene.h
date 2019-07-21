#pragma once
#ifndef INCLUDED_GAME_SCENE_H_
#define INCLUDED_GAME_SCENE_H_

#include "Scene.h"

#include "BoardCellType.h"
#include "BoardInfo.h"

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
	void boardInit();

	bool putStone();	//�΂��u�����ꍇtrue��Ԃ�
	bool isPutedStone();	//�����ɐ΂��u����̂�

	bool leftTurnOverCheck() const;
	bool rightTurnOverCheck() const;
	bool topTurnOverCheck() const;
	bool underTurnOverCheck() const;
	bool top_leftTurnOverCheck() const;
	bool top_rightTurnOverCheck() const;
	bool under_leftTurnOverCheck() const;
	bool under_rightTurnOverCheck() const;

	void drawBoard() const;
	void drawStone() const;	//�Տ�̐΂�`��
	void textRender() const;
	

	void playerSwitching();
	bool isGameOver();
	bool isCursorOnBoard() const;
	int frameCount;		//���t���[������������J�E���g
	bool gameOverFlag;

	BoardCellType board[BOARD_LINE_CELL_NUM][BOARD_ROW_CELL_NUM];
	int mousePosX, mousePosY;
	int cellX, cellY;	//�{�[�h�̃}�X�̈ʒu

	int playerStoneNum[PLAYER_NUM];
	int turnPlayerNum;	//��Ԃ̃v���C���[�ԍ�
};


#endif // !INCLUDED_GAME_SCENE_H_

