#ifndef FACILITY_H_
#define FACILITY_H_

#include"../GameManager/gameManager.h"

//�{��
class Facility
{
private:
	Image image;
	int aitemCount;

public:
	Facility();
	~Facility();
	void initialize();
	void update(float frameTime);
	void draw();
	

};

#endif