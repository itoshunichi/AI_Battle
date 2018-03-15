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
	//FormCharacter &otherFormCharacter = FormCharacter();
	Input *input;
	Image image;
	Vector2 position;
	int playerNum;
	Entity myShop;
	//��������L�����N�^�[�̃��X�g
	vector<CharacterType>formCharacterTypes;
	//���������܂ǂ��̗�ɂ��邩
	int currentRow;
	//��������L�����N�^�[�̃��X�g
	list<Character*>formCharacters;
	//1��ڂ̃L����
	list<Character*>firstColumnCharacters;
	//2��ڂ̃L����
	list<Character*>secondColumnCharacters;
	//3��ڂ̃L����
	list<Character*>thirdColumnCharacters;

private:
	void formSelectCharacter(CharacterType type);
	void formCharacter();
	void setCurrentRow();
	Vector2 formPosition();
	void removeCharacter();
public:
	FormCharacter();
	FormCharacter(GameManager *gameManager,Entity &myShop,int playerNum);
	~FormCharacter();
	void initalize();
	void update(float frameTime,FormCharacter &formCharacter);
	void draw();
	void move();
	void addCharacterType(CharacterType type){ formCharacterTypes.push_back(type); }
	//�񂲂Ƃ̃��X�g�ɒǉ�
	void addColumnCharacters(Character* character);
	
	list<Character*>getFormCharacters(){ return formCharacters; }
	list<Character*>getFirstColumnCharacters(){ return firstColumnCharacters; }
	list<Character*>getSecondColumnCharacters(){ return secondColumnCharacters; }
	list<Character*>getThirdColumnCharacters(){ return thirdColumnCharacters; }
	//vector<Character*>*getFormCharacters{ return &formCharacters; }
};

#endif