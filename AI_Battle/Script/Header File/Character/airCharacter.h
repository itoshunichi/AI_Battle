#ifndef AIRCHARACTER_H_
#define AIRCHARACTER_H_

#include"character.h"

//空のキャラクター
class AirCharacter :public Character
{
public:
	AirCharacter();
	~AirCharacter();
protected:
	void setPosition(float pointPositionX, int pointRow);
	void attackSetDegress();
	////攻撃開始
	//void startAttack(Character* characters);
};

#endif