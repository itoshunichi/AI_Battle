#include"../../Header File/Scene/sceneManager.h"

SceneManager::SceneManager()
{

}

/*�R���X�g���N�^*/
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

/*�e�V�[����ǉ�*/
void SceneManager::addScene()
{
	scenes.insert(map<SceneMode, Scene*>::value_type(SceneMode::TITLE, &title));
	scenes.insert(map<SceneMode, Scene*>::value_type(SceneMode::GAMEPLAY, &gamePlay));
	scenes.insert(map<SceneMode, Scene*>::value_type(SceneMode::GAMECLEAR, &gameClear));
	scenes.insert(map<SceneMode, Scene*>::value_type(SceneMode::GAMEOVER, &gameOver));

}

/*���݂̃V�[���ύX*/
void SceneManager::change(SceneMode name)
{
	currentScene = scenes[name];
	currentScene->initialize();
}

/*���݂̃V�[����`��*/
void SceneManager::draw()
{
	
	if (currentScene == NULL)
	{
		return;
	}

	currentScene->draw();
}

/*���݂̃V�[���̍X�V*/
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
