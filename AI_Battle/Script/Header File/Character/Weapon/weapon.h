#ifndef WEAPON_H_
#define WEAPON_H_

#include"../../Default/entity.h"
#include"../direction.h"
#include"../character.h"
#include"../../Otherwise/math.h"

class Weapon:public Entity
{
protected:
	GameManager *gameManager;
	//移動速度
	float speed;
	//向き
	Direction direction;
	float damage;
	Vector2 targetCharacterPosition;
	float targetRadian;
public:
	Weapon();
	~Weapon();
	bool collisionCharacter(Character* characterEntity);
	//初期化
	virtual void initialize() = 0;
	//更新
	virtual void update(float frameTime) = 0;
	//描画
	virtual void draw() = 0;
	void setDamage(float damage){ this->damage = damage; }
protected:
	void move(float frameTime);
	//ターゲットまでの角度
	void setTargetRadian();
};

#endif