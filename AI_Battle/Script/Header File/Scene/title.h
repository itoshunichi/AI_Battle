#ifndef _TITLE_
#define _TITLE_

#include"../Default/TextDX.h"
#include"scene.h"


class Title:public Scene
{
private:
	Image titleImage;
	TextDX text;
public:
	Title();
	Title(GameManager *gameManager);
	void draw();
	void initialize();
	void update(float frameTime);
	void collision();
	SceneMode Next();

private:
	void endScene();

};

#endif