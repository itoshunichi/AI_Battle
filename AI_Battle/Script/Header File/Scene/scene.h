#ifndef SCENE_H_
#define SCENE_H_

#include"../Default/game.h"
#include"sceneMode.h"
#include"../Otherwise/Fade.h"
#include"../GameManager/gameManager.h"

class Scene
{
//•Ï”
protected:
	Input *input;
	bool isEnd;
	Fade fade;

	GameManager *gameManager;

//ŠÖ”
public:
	virtual void initialize() = 0;
	virtual void update(float frameTime) = 0;
	virtual void draw() = 0;
	virtual void collision() = 0;
	virtual SceneMode Next() = 0;
	bool isSceneEnd(){ return isEnd; }
protected:
	virtual void endScene() = 0;
	

}; 

#endif