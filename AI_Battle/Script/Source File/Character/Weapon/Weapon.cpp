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
	setTargetRadian();
	position.x += Math::cos(targetRadian);
	position.y += Math::sin(targetRadian);

}

void Weapon::setTargetRadian()
{
	float w = targetCharacterPosition.x - position.x;
	float h = targetCharacterPosition.y - position.y;

	targetRadian = Math::atan(h, w);
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