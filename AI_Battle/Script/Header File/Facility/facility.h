#ifndef FACILITY_H_
#define FACILITY_H_

#include"../GameManager/gameManager.h"

//施設
class Facility
{
private:
	GameManager *gameManager;
	Image image;
	Image aitemIcon;
	vector<Image>aitemIcons;
	int aitemCount;
	Vector2 position;

private:
	//アイテムのアイコンの位置の設定
	void setAitemIconsPosition();
public:
	Facility();
	Facility(GameManager *gameManager);
	~Facility();
	void initialize();
	void update(float frameTime);
	void draw();
	void setPosition(Vector2 position){ this->position = position; image.setX(position.x); image.setY(position.y); }
	

};

#endif