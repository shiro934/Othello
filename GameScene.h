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

	bool putStone();	//石が置けた場合trueを返す
	bool isPutedStone();	//そこに石が置けるのか

	bool leftTurnOverCheck() const;
	bool rightTurnOverCheck() const;
	bool topTurnOverCheck() const;
	bool underTurnOverCheck() const;
	bool top_leftTurnOverCheck() const;
	bool top_rightTurnOverCheck() const;
	bool under_leftTurnOverCheck() const;
	bool under_rightTurnOverCheck() const;

	void drawBoard() const;
	void drawStone() const;	//盤上の石を描画
	void textRender() const;
	

	void playerSwitching();
	bool isGameOver();
	bool isCursorOnBoard() const;
	int frameCount;		//何フレーム回ったかをカウント
	bool gameOverFlag;

	BoardCellType board[BOARD_LINE_CELL_NUM][BOARD_ROW_CELL_NUM];
	int mousePosX, mousePosY;
	int cellX, cellY;	//ボードのマスの位置

	int playerStoneNum[PLAYER_NUM];
	int turnPlayerNum;	//手番のプレイヤー番号
};


#endif // !INCLUDED_GAME_SCENE_H_

