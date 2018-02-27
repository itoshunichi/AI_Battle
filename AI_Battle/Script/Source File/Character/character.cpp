#include"../../Header File/Character/character.h"

Character::Character()
{

}

Character::~Character()
{

}

void Character::setAngle()
{
	if (direction == Direction::UP)
	{
		currentImage.setDegress(0);
	}
	if (direction == Direction::DOWN)
	{
		currentImage.setDegress(180);
	}
	if (direction == Direction::RIGHT)
	{
		currentImage.setDegress(90);
	}
	if (direction == Direction::LEFT)
	{
		currentImage.setDegress(270);
	}
}