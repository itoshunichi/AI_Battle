#ifndef _GAMECLEAR_
#define _GAMECLEAR_

#include"../Default/game.h"
#include"scene.h"

class GameClear:public Scene
{
private:

public:
	GameClear();
	GameClear(GameManager *gameManager);
	void draw();
	void initialize();
	void update(float frameTime);
	void collision();
	SceneMode Next();
private:
	void endScene();

};

#endif