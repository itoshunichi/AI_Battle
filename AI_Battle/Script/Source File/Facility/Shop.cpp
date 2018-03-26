#include"../../Header File/Facility/shop.h"

Shop::Shop()
{

}

Shop::Shop(GameManager *gameManager,PlayerNum playerNum)
{
	this->gameManager = gameManager;
	this->playerNum = playerNum;
	collisionType = entityNS::COLLISION_TYPE::BOX;
	collisionTag = entityNS::COLLISION_TAG::FACILITY;
}

Shop::~Shop()
{
	
}

//‰Šú‰»
void Shop::initialize()
{
	maxCustonerCount = 6;
	customerCount = 3;
	currentImage = gameManager->getImageManager()->getFacility_Image();
	customerIcon = gameManager->getImageManager()->getAitemIcon_Image();
	for (int i = 0; i < maxCustonerCount; i++)
	{
		customerIcons.push_back(customerIcon);
	}
	//‰¼
	if (isPlayer1())
	{
		setPosition(vector2(0, 0));
	}
	if (isPlayer2())
	{
		setPosition(vector2(GAME_WIDTH - 128, 0));
	}

}

//XV
void Shop::update(float frameTime)
{
	Entity::update(frameTime);
	setAitemIconsPosition();
	
}

//•`‰æ
void Shop::draw()
{
	//currentImage.draw();
	for (int i = 0; i < customerCount; i++)
	{
		customerIcons[i].draw();
	}
}

void Shop::setAitemIconsPosition()
{
	for (int i = 0; i < customerCount; i++)
	{
		
		if (i < 3)
		{
			customerIcons[i].setX(position.x + (i*customerIcon.getWidth()) + i * 5);
			customerIcons[i].setY(0);
		}
		else if (i>2)
		{
			customerIcons[i].setX(position.x + ((i-3)*customerIcon.getWidth()) + (i-3) * 5);
			customerIcons[i].setY(customerIcon.getHeight()+10);
		}
	}

}