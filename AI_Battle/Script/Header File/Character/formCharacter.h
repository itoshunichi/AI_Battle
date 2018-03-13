#ifndef FORMCHARACTER_H_
#define FORMCHARACTER_H_

#include"../GameManager/gameManager.h"
#include"../Default/entity.h"
#include"../Otherwise/math.h"
#include"../Character/character.h"
#include"testCharacter.h"
#include"characterType.h"

class FormCharacter
{
private:
	GameManager *gameManager;
	Input *input;
	Image image;
	Vector2 position;
	int playerNum;
	Entity myShop;
	//生成するキャラクターのリスト
	vector<CharacterType>formCharacterTypes;
	//自分がいまどこの列にいるか
	int currentRow;

private:
	void formSelectCharacter(CharacterType type);
	void formCharacter();
	void setCurrentRow();
	Vector2 formPosition();
public:
	FormCharacter();
	FormCharacter(GameManager *gameManager,Entity &myShop,int playerNum);
	~FormCharacter();
	void initalize();
	void update(float frameTime);
	void draw();
	void move();
	void addCharacterType(CharacterType type){ formCharacterTypes.push_back(type); }
	vector<Character*>formCharacters;
	//vector<Character*>*getFormCharacters{ return &formCharacters; }
};

#endif