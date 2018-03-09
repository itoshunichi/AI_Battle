#ifndef CHARACTER_H_
#define CHARACTER_H_

#include"../Default/entity.h"
#include"direction.h"
#include"square.h"

class Character :public Entity
{
public:
	//���
	enum Type
	{
		LAND,//��
		SKY,//��
	};

	//���
	enum Mode
	{
		APPEARANCE,//�o��
		MOVE,//�ړ�
		ATTACK,//�U��
		ARRIVAL,//����
		DEAD,//���S
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
	//���݂̏��
	Mode mode;
	//�v���C���[�ԍ�
	int playerNum;
	//�����̓X
	Entity myShop;
	//����̓X
	Entity otherShop;

protected:
	void setPosition();
	//�p�x�̐ݒ�
	void setAngle();
	//�o��
	void appearance();
	//�ړ�����
	void move(float frameTime);
	//�����ύX
	void changeDirection();
public:
	Character();
	~Character();
	//������
	virtual void initialize() = 0;
	//�X�V
	virtual void update(float frameTime) = 0;
	//�`��
	virtual void draw() = 0;
	//����X�Ƃ̏Փ˔���
	virtual void otherShopCollision(Entity &entity,int &customerCount);
	//�����X�Ƃ̏Փ˔���
	virtual void myShopColiision(Entity &entity, int &customerCout);
	void setPosition(Vector2 position){ this->position = position; }
	SQUARE getCurrentSquare(){ return currentSquare; }
	

private:
	
	
};

#endif