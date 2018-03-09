#ifndef _ENTITY_H
#define _ENTITY_H
#define WIN32_LEAN_AND_MEAN

#include "image.h"
#include"Input.h"
#include"game.h"
#include"../GameManager/gameManager.h"

namespace entityNS
{
	enum COLLISION_TYPE{NONE,CIRCLE,BOX,ROTATED_BOX};//�����蔻��̎��
	enum COLLISION_TAG{FACILITY,CHARACTER};
	const float GRAVITY = 6.67428e-11f; 
}

class Entity
{
protected:
	string tag;
	GameManager *gameManager;
	ImageManager *imageManager;
	Vector2 position;
	Image currentImage;
	entityNS::COLLISION_TYPE collisionType;
	entityNS::COLLISION_TAG collisionTag;
	Vector2 center;//�G���e�B�e�B�̒��S�_
	float radius;//�~�̔��a
	Vector2 distSqured;
	float sumRadiiSquared;
	RECT edge;//�Z�a�̈�
	Vector2 corners[4];
	Vector2 edge01, edge03;
	float edge01Min, edge01Max, edge03Max, edge03Min;
	Vector2 velocity;//���݂̃G���e�B�e�B�̑��x���܂ރx�N�g��
	Vector2 deltaV;
	float mass;//�G���e�B�e�B�̎���
	float health;//�G���e�B�e�B�̗̑�
	float rr;
	float force;
	float gravity;//�d��
	Input *input;
	HRESULT hr;
	bool active;//���݂̏�ԁB�A�N�e�B�u�ȃG���e�B�e�B�݂̂��Փ˂��N�����B
	float rotatedBoxReady;
	Vector2 collisionVelocity;

	//�~�̏Փ˔��胁�\�b�h
	virtual bool collideCircle(Entity &ent);
	//�����s���E�{�b�N�X�̏Փ˔��胁�\�b�h
	virtual bool collideBox(Entity &ent);
	//��]����{�b�N�X�̏Փ˔��胁�\�b�h
	virtual bool collideRotatedBox(Entity &ent);
	//��]����{�b�N�X�Ɖ~�̏Փ˔��胁�\�b�h
	virtual bool collideRotatedBoxCircle(Entity &ent);
	//��]����{�b�N�X�̒��_�A���e���A���e�̍ŏ��l�ƍő�l���v�Z
	void computeRotatedBox();
	//����̃{�b�N�X���A���̃G���e�B�e�B��edge01�����edge03�ɓ��e
	bool projectionsOverlap(Entity &ent);
	//�{�b�N�X�̒��_���~�ƏՓ˂��Ă��Ȃ������A�����̃`�F�b�N���g�p���Ĕ���
	bool collideCornerCircle(Vector2 corner, Entity &ent);

public:
	Entity();
	//Entity(GameManager *gameManager);
	virtual ~Entity(){}

	virtual const Vector2 getCenter()
	{
		center = vector2(currentImage.getCenterX(), currentImage.getCenterY());
		return center;
	}

	virtual float getRadius()const{ return radius; }

	virtual const RECT& getEdge()const { return edge; }

	virtual const Vector2* getCorner(UINT c)const
	{
		if (c >= 4)
			c = 0;
		return &corners[c];
	}

	virtual Vector2 getPosition()const{ return position; }
	virtual const Vector2 getVelocity()const { return velocity; }

	virtual string getTag()const { return tag; }

	virtual bool getActive()const { return active; }

	virtual float getMass()const { return mass; }

	virtual float getGravity() const{ return gravity; }

	virtual float getHealth() const { return health; }

	virtual Image getCurrentImage() const{ return currentImage; }

	virtual entityNS::COLLISION_TYPE getCollisionType(){ return collisionType; }

	virtual entityNS::COLLISION_TAG getCollisionTag(){ return collisionTag; }

	virtual void setPosition(Vector2 position){ this->position = position; }

	virtual void setVelocity(Vector2 v){ velocity = v; }

	virtual void setDeltaV(Vector2 dv){ deltaV = dv; }

	virtual void setActive(bool a){ active = a; }

	virtual void setHealth(float h){ health = h; }

	virtual void setMass(float m){ mass = m; }

	virtual void setGravity(float g){ gravity = g; }

	virtual void setCollisionRadius(float r){ radius = r; }

	virtual void setCurrentImage(Image currentImage){ this->currentImage = currentImage; }

	//������
	/*virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM);*/

	//�X�V
	virtual void update(float frameTime);

	virtual void activate();

	virtual void ai(float frameTime, Entity &ent);

	virtual bool outsideRect(RECT rect);

	virtual bool collideWith(Entity &ent,entityNS::COLLISION_TAG collisionTag);

	virtual void damage(int weapon);

	void bounce(Vector2 &collisionVector, Entity &ent);

	void gravityForce(Entity *other, float frameTime);
};

#endif