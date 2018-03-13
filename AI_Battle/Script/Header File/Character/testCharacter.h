#include"../Character/character.h"


class TestCharacter:public Character
{
public:
	TestCharacter();
	TestCharacter(GameManager *gameManager,Vector2 position,int pleryNum);
	~TestCharacter();
	void initialize();
	void update(float frameTime);
	void draw();

};