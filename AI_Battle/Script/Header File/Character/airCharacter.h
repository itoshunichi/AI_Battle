#ifndef AIRCHARACTER_H_
#define AIRCHARACTER_H_

#include"character.h"

//��̃L�����N�^�[
class AirCharacter :public Character
{
public:
	AirCharacter();
	~AirCharacter();
protected:
	void setPosition(float pointPositionX, int pointRow);
	void attackSetDegress();
	////�U���J�n
	//void startAttack(Character* characters);
};

#endif