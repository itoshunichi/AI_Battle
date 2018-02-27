#ifndef FADE_H_
#define FADE_H_

#include"../GameManager/imageManager.h"
#include"../Default/game.h"
#include"../Default/image.h"

enum Mode
{
	FADEIN,
	FADEOUT,
};
class Fade
{
public:
	Fade();
	Fade(ImageManager *gameTexture);
	void update();
	void initialize();
	void draw();
	void setMode(Mode mode){ this->mode = mode; }
	bool getIsEnd(){ return isEnd; }
	void fadeOutStart();

private:
	bool isEnd;
	Mode mode;
	int alpha;
	Image image;
	ImageManager *gameTexture;

};

#endif