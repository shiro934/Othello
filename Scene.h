#pragma once
#ifndef INCLUDED_SCENE_H_
#define INCLUDED_SCENE_H_

#include "InputKey.h"
#include "InputMouse.h"
#include "SceneType.h"

class Scene
{
public:
	Scene();
	~Scene();

	virtual void input(const InputKey& key, const InputMouse& mouse) = 0;
	virtual void update() = 0;
	virtual void render() const = 0;

	virtual SceneType nextSceneType() const = 0;	//次のシーンタイプを返す

	bool isNextScene() const { return nextSceneFlag; }	//シーン遷移をするか返す
protected : 
	bool nextSceneFlag;
};


#endif // !INCLUDED_SCENE_H_
