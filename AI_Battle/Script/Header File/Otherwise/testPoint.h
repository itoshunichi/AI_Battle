#ifndef _TESTPOINT_H
#define _TESTPOINT_H
#define WIN32_LEAN_AND_MEAN

#include"../GameManager/gameManager.h"
#include"../Default/entity.h"

class TestPoint
{
private:
	Image image;
	Vector2 position;
	ImageManager *imageManager;
public:
	TestPoint();
	TestPoint(Vector2 position, GameManager *gameManager);
	void draw();
	void initialize();

};

#endif