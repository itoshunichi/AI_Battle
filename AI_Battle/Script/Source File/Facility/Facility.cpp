#include"../../Header File/Facility/facility.h"

Facility::Facility()
{

}

Facility::Facility(GameManager *gameManager)
{
	this->gameManager = gameManager;
}

Facility::~Facility()
{

}

//‰Šú‰»
void Facility::initialize()
{
	aitemCount = 3;
	image = gameManager->getImageManager()->getFacility_Image();
	aitemIcon = gameManager->getImageManager()->getAitemIcon_Image();
	for (int i = 0; i < aitemCount; i++)
	{
		aitemIcons.push_back(aitemIcon);
	}
}

//XV
void Facility::update(float frameTime)
{
	
	setAitemIconsPosition();
}

//•`‰æ
void Facility::draw()
{
	image.draw();
	for (int i = 0; i < aitemIcons.size(); i++)
	{
		aitemIcons[i].draw();
	}
}

void Facility::setAitemIconsPosition()
{
	for (int i = 0; i < aitemIcons.size(); i++)
	{
		aitemIcons[i].setX(position.x + (i*aitemIcon.getWidth())+i*5);
		aitemIcons[i].setY(0);
	}

}