#ifndef CHARACTER_H_
#define CHARACTER_H_

#include"../Default/entity.h"
#include"direction.h"
#include"square.h"

class Character :public Entity
{
	//���
	enum Type
	{
		LAND,//��
		SKY,//��
	};

	//�U�����@
	enum AttackType
	{
		NONE,//����
		PROXIMITY,//�ߐ�
		LONG_DISTANCE,//������

	};
	//�X�e�[�^�X
	struct States
	{
		int hp;//�̗�
		int attackPower;//�U����
		float attackTime;//�U�����x
		float moveSpeed;//�ړ����x
		float attackRange;//�U���͈�

	};
protected:
	//���
	Type type;
	//�U�����@
	AttackType attackType;
	//�X�e�[�^�X
	States states;

	//���݂̃}�X
	SQUARE currentSquare;
	//���݂̌���
	Direction direction;
	//�p�x�̐ݒ�
	void setAngle();
public:
	Character();
	~Character();
	//������
	virtual void initialize() = 0;
	//�X�V
	virtual void update(float frameTime) = 0;
	//�`��
	virtual void draw() = 0;

	SQUARE getCurrentSquare(){ return currentSquare; }
};

#endif