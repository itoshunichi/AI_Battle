#include"../../Header File/Scene/sceneManager.h"

SceneManager::SceneManager()
{

}

/*コンストラクタ*/
SceneManager::SceneManager(GameManager *gameManager)
{
	title = Title(gameManager);
	gamePlay = GamePlay(gameManager);
	gameClear = GameClear(gameManager);
	gameOver = GameOver(gameManager);
}


SceneManager::~SceneManager()
{
	
}

/*各シーンを追加*/
void SceneManager::addScene()
{
	scenes.insert(map<SceneMode, Scene*>::value_type(SceneMode::TITLE, &title));
	scenes.insert(map<SceneMode, Scene*>::value_type(SceneMode::GAMEPLAY, &gamePlay));
	scenes.insert(map<SceneMode, Scene*>::value_type(SceneMode::GAMECLEAR, &gameClear));
	scenes.insert(map<SceneMode, Scene*>::value_type(SceneMode::GAMEOVER, &gameOver));

}

/*現在のシーン変更*/
void SceneManager::change(SceneMode name)
{
	currentScene = scenes[name];
	currentScene->initialize();
}

/*現在のシーンを描画*/
void SceneManager::draw()
{
	
	if (currentScene == NULL)
	{
		return;
	}

	currentScene->draw();
}

/*現在のシーンの更新*/
void SceneManager::update(float frameTime)
{
	if (currentScene == NULL)
	{
		return;
	}

	currentScene->update(frameTime);

	if (currentScene->isSceneEnd())
	{
		change(currentScene->Next());
	}

}

void SceneManager::collision()
{
	currentScene->collision();
}
