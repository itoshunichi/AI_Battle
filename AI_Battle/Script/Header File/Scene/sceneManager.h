#ifndef _SCENEMANAGER_
#define _SCENEMANAGER_


#include"title.h"
#include"gamePlay.h"
#include"gameClear.h"
#include"gameOver.h"
#include<map>
#include"../Default/TextDX.h"
#include"../GameManager/soundManager.h"
#include"../GameManager/gameManager.h"


class SceneManager
{
public:
	SceneManager();
	SceneManager(GameManager *gameManager);
	~SceneManager();
	void draw();
	void update(float frameTime);
	void collision();
	void change(SceneMode name);
	void addScene();
	bool getIsEnd(){ return isEnd; };

private:
	Title title;
	GamePlay gamePlay;
	GameClear gameClear;
	GameOver gameOver;
	Scene *currentScene;
	map<SceneMode, Scene*> scenes;
	TextDX text;
	bool isEnd;

	

};

#endif