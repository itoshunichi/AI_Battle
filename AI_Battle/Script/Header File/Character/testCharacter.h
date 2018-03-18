#include"../Character/proximityAttackCharacter.h"
#include"Status\status_TestCharacter.h"

class TestCharacter:public ProximityAttackCharacter
{
public:
	TestCharacter();
	TestCharacter(GameManager *gameManager,Vector2 position,int pleryNum);
	~TestCharacter();
	void initialize();
	void update(float frameTime);
	void draw();

};