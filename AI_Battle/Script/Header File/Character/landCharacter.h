#ifndef LANDCHARACTER_H_
#define LANDCHARACTER_H_

#include"character.h"
//陸上のキャラクター
class LandCharacter:public Character
{
public:
	LandCharacter();
	~LandCharacter();
protected:
	void setPosition(float pointPositionX, int pointRow);
	////攻撃開始
	//void startAttack(Character* characters);
};

#endif