#ifndef WEAPON_H_
#define WEAPON_H_

#include"../../Default/entity.h"
#include"../direction.h"
#include"../character.h"

class Weapon:public Entity
{
protected:
	GameManager *gameManager;
	//ˆÚ“®‘¬“x
	float speed;
	//Œü‚«
	Direction direction;
	float damage;
public:
	Weapon();
	//Weapon(GameManager *gameManager,Character *character,Vector2 position);
	~Weapon();
	bool collisionCharacter(Character* characterEntity);
	//‰Šú‰»
	virtual void initialize() = 0;
	//XV
	virtual void update(float frameTime) = 0;
	//•`‰æ
	virtual void draw() = 0;
	void setDamage(float damage){ this->damage = damage; }
protected:
	void move(float frameTime);

};

#endif