#ifndef _ENTITY_H
#define _ENTITY_H
#define WIN32_LEAN_AND_MEAN

#include "image.h"
#include"Input.h"
#include"game.h"
#include"../GameManager/gameManager.h"

namespace entityNS
{
	enum COLLISION_TYPE{NONE,CIRCLE,BOX,ROTATED_BOX};//あたり判定の種類
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
	Vector2 center;//エンティティの中心点
	float radius;//円の半径
	Vector2 distSqured;
	float sumRadiiSquared;
	RECT edge;//短径領域
	Vector2 corners[4];
	Vector2 edge01, edge03;
	float edge01Min, edge01Max, edge03Max, edge03Min;
	Vector2 velocity;//現在のエンティティの速度を含むベクトル
	Vector2 deltaV;
	float mass;//エンティティの質量
	float health;//エンティティの体力
	float rr;
	float force;
	float gravity;//重力
	Input *input;
	HRESULT hr;
	bool active;//現在の状態。アクティブなエンティティのみが衝突を起こす。
	float rotatedBoxReady;
	Vector2 collisionVelocity;

	//円の衝突判定メソッド
	virtual bool collideCircle(Entity &ent);
	//軸平行境界ボックスの衝突判定メソッド
	virtual bool collideBox(Entity &ent);
	//回転するボックスの衝突判定メソッド
	virtual bool collideRotatedBox(Entity &ent);
	//回転するボックスと円の衝突判定メソッド
	virtual bool collideRotatedBoxCircle(Entity &ent);
	//回転するボックスの頂点、投影線、投影の最小値と最大値を計算
	void computeRotatedBox();
	//相手のボックスを、このエンティティのedge01およびedge03に投影
	bool projectionsOverlap(Entity &ent);
	//ボックスの頂点が円と衝突していないかを、距離のチェックを使用して判定
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

	//初期化
	/*virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM);*/

	//更新
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