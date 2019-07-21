#include "SceneManager.h"

#include "TitleScene.h"
#include "GameScene.h"

#include <windows.h>

#include <cassert>

SceneManager::SceneManager()
{
	currentScene = new TitleScene();
}


SceneManager::~SceneManager()
{
	delete currentScene;
}

void SceneManager::input(const InputKey& key, const InputMouse& mouse) const {
	assert(currentScene != nullptr);
	currentScene->input(key, mouse);
}

void SceneManager::update() const {
	assert(currentScene != nullptr);
	currentScene->update();
}

void SceneManager::render() const {
	assert(currentScene != nullptr);
	currentScene->render();
}

void SceneManager::sceneChange() {
	assert(currentScene != nullptr);

	//シーン遷移するかをチェック
	if (currentScene->isNextScene() == false) {
		return;
	}

	SceneType nextScene = currentScene->nextSceneType();

	if (currentScene) {
		delete currentScene;
	}

	switch (nextScene)
	{
	case TITLE:
		currentScene = new TitleScene();
		break;
	case GAME:
		currentScene = new GameScene();
		break;
	default:
		MessageBox(nullptr, TEXT("nextSceneが正しくありません")
			, TEXT("エラー"), MB_OK);
		break;
	}

}