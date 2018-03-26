#ifndef CHARACTER_H_
#define CHARACTER_H_

#include"../Default/entity.h"
#include"direction.h"
#include"square.h"
#include"../Otherwise/timer.h"
#include"Status\status.h"
#include"playerNum.h"

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
		TRANSPORT,//�^��
		DEAD,//���S
	};

	//�U�����@
	enum AttackType
	{
		NONE,//����
		PROXIMITY,//�ߐ�
		LONG_DISTANCE,//������

	};
protected:
	//���
	Type type;
	//�U�����@
	AttackType attackType;
	//�X�e�[�^�X
	Status* status;
	//���݂̃}�X
	SQUARE currentSquare;
	//���݂̌���
	Direction direction;
	//���݂̏��
	Mode mode;
	//�v���C���[�ԍ�
	PlayerNum playerNum;
	//���݂̗�
	int currentRow;
	//���݂�HP
	int currentHp;
	//�U���̑Ώ�
	Character* attackTargetCharacter;
protected:
	
	//�p�x�̐ݒ�
	void setAngle();
	//�o��
	void appearance();
	//�ړ�����
	void move(float frameTime);
	//�U������
	//void attack(float frameTime);
	void dead();
	//�E�������ǂ���
	bool isDirectionRight(){ return direction == Direction::RIGHT; }
	//���������ǂ���
	bool isDirectionLeft(){ return direction == Direction::LEFT; }
	//1P���ǂ���
	bool isPlayer1(){ return playerNum == PlayerNum::PLAYER1; }
	//2P��
	bool isPlayer2(){ return playerNum == PlayerNum::PLAYER2; }
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
	virtual void setPosition(float pointPositionX, int pointRow) = 0;
	//����X�Ƃ̏Փ˔���
	virtual void otherShopCollision(Entity &entity,int &customerCount);
	//�����X�Ƃ̏Փ˔���
	virtual void myShopColiision(Entity &entity, int &customerCout);
	//�U���J�n
	virtual void startAttack(Character* characters) = 0;
	//�U������
	virtual void attack(float frameTime) = 0;
	SQUARE getCurrentSquare(){ return currentSquare; }
	void damage(float damage);
	//��Ԃ̕ύX
	void changeMode(Mode mode){ this->mode = mode;}
	//�̗͎擾
	int getHp(){ return currentHp; }
	//���݂̗���擾
	int getCurrentRow(){ return currentRow; }
	//��Ԃ̎擾
	Mode getMode(){ return mode; }
	//�R�X�g�̎擾
	int getCost(){ return status->cost; }
	Type getType(){ return type; }
};

#endif