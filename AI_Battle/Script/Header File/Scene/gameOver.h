#ifndef _GAMEOVER_
#define _GAMEOVER_

#include"scene.h"

class GameOver:public Scene
{
private:
	
public:
	GameOver();
	GameOver(GameManager *gameManager);
	void draw();
	void initialize();
	void update(float frameTime);
	void collision();
	SceneMode Next();
private:
	void endScene();
};
#endif