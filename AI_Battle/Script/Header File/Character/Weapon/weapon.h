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
	//�ړ����x
	float speed;
	//����
	Direction direction;
	float damage;
	Vector2 targetCharacterPosition;
	float targetRadian;
public:
	Weapon();
	~Weapon();
	bool collisionCharacter(Character* characterEntity);
	//������
	virtual void initialize() = 0;
	//�X�V
	virtual void update(float frameTime) = 0;
	//�`��
	virtual void draw() = 0;
	void setDamage(float damage){ this->damage = damage; }
protected:
	void move(float frameTime);
	//�^�[�Q�b�g�܂ł̊p�x
	void setTargetRadian();
};

#endif