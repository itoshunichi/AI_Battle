#include"../../../Header File/Character/Weapon/weapon.h"

Weapon::Weapon()
{

}

Weapon::~Weapon()
{

}

//ˆÚ“®ˆ—
void Weapon::move(float frameTime)
{
	if (direction == Direction::RIGHT)
	{
		position.x += speed*frameTime;
	}
	else if (direction == Direction::LEFT)
	{
		position.x -= speed*frameTime;
	}
}

bool Weapon::collisionCharacter(Character* character)
{
	if (Entity::collideWith(*character, entityNS::COLLISION_TAG::CHARACTER))
	{
		character->damage(damage);
		return true;
		//delete this;
	}
	return false;
}