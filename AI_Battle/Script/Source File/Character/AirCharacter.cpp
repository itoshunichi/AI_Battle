#include"../../Header File/Character/airCharacter.h"

AirCharacter::AirCharacter()
{
	type = Type::SKY;
}

AirCharacter::~AirCharacter()
{

}

void AirCharacter::setPosition(float pointPositionX, int pointRow)
{
	if (pointRow == 1)
	{
		position = vector2(pointPositionX, firstColumnMinY);
	}
	else if (pointRow == 2)
	{
		position = vector2(pointPositionX, seconsColumnMinY);
	}
	else if (pointRow == 3)
	{
		position = vector2(pointPositionX, thirdColumnMinY);
	}
	position.y -= currentImage.getHeight();
	
}

void AirCharacter::attackSetDegress()
{
	if (attackTargetCharacter->getPosition().x > position.x)
	{
		currentImage.setDegress(45);
	}
	else

	{
		currentImage.setDegress(-45);
	}
}
