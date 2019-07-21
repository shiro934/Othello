#pragma once
#ifndef INCLUDED_SCENE_MANAGER_H_
#define INCLUDED_SCENE_MANAGER_H_

#include "Scene.h"
#include "InputKey.h"
#include "InputMouse.h"

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void input(const InputKey& key, const InputMouse& mouse) const;
	void update() const;
	void render() const;

	void sceneChange();	//ÉVÅ[ÉìêÿÇËë÷Ç¶
private : 
	Scene* currentScene;
};

#endif // !INCLUDED_SCENE_MANAGER_H_
