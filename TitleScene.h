#pragma once
#ifndef INCLUDED_TITLE_SCENE_H_
#define INCLUDED_TITLE_SCENE_H_

#include "Scene.h"

class TitleScene :
	public Scene
{
public:
	TitleScene();
	~TitleScene();

	void input(const InputKey& key, const InputMouse& mouse) override;
	void update() override;
	void render() const override;

	SceneType nextSceneType() const override;

private : 
	int frameCount;
};

#endif // !INCLUDED_TITLE_SCENE_H_
