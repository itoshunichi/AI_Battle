#ifndef GAMEMANAGER_H_
#define GAMEMANAGER_H_

#include"../Default/Input.h"
#include"imageManager.h"
#include"soundManager.h"

class GameManager
{
private:
	SoundManager *soundManager;
	ImageManager *imageManager;
	Input *input;
	Graphics *graphics;
	TextDX *text;
	Console *console;

public:
	GameManager();
	void initialize(Game *game, HWND hwnd);
	SoundManager* getSoundManager(){ return soundManager; }
	ImageManager* getImageManager(){ return imageManager; }
	Input* getInput(){ return input; }
	Graphics* getGraphics(){ return graphics; }
	TextDX* getTextDX(){ return text; }
	Console* getConsole(){ return console; }
};

#endif