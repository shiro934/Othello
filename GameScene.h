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
	int cellX, cellY;	//ボードのマスの位置

	int turnPlayerNum;	//手番のプレイヤー番号
	int passNum = 0;		//連続パス数
	bool isTurnPlayerPutedCheck;	//手番のプレイヤーが石を置けるかを記憶しておく

	bool turnSwitchFlag = true;	//trueなら石を置くと手番が変わる
};


#endif // !INCLUDED_GAME_SCENE_H_

