#ifndef LANDCHARACTER_H_
#define LANDCHARACTER_H_

#include"character.h"
//����̃L�����N�^�[
class LandCharacter:public Character
{
public:
	LandCharacter();
	~LandCharacter();
protected:
	void setPosition(float pointPositionX, int pointRow);
	////�U���J�n
	//void startAttack(Character* characters);
};

#endif