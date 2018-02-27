#include"../../Header File/Otherwise/testPoint.h"

TestPoint::TestPoint()
{

}

TestPoint::TestPoint(Vector2 position, GameManager *gameManager)
{
	this->position = position;
	this->imageManager = gameManager->getImageManager();
	initialize();
}

void TestPoint::initialize()
{
	image = imageManager->getTestPointImage();
	image.setX(position.x);
	image.setY(position.y);
}

void TestPoint::draw()
{
	image.draw();
}
