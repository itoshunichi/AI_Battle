#ifndef FORMCHARACTER_H_
#define FORMCHARACTER_H_

#include"../GameManager/gameManager.h"
#include"../Default/entity.h"
#include"../Otherwise/math.h"
#include"../Character/character.h"
#include"testCharacter.h"
#include"longAttackTestCharacter.h"
#include"characterType.h"

//�L�����N�^�[�𐶐�����N���X
class FormCharacter
{
private:
	GameManager *gameManager;
	Input *input;
	//�����|�C���g�̉摜
	Image pointImage;
	//�����|�C���g�̍��W
	Vector2 pointPosition;
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
	//���݂���̗��ݒ�
	void setCurrentRow();
	//��������ʒu
	Vector2 formPosition();
	//�L�����N�^�[�̍폜
	void removeCharacter();
public:
	FormCharacter();
	FormCharacter(GameManager *gameManager,Entity &myShop,int playerNum);
	~FormCharacter();
	//������
	void initalize();
	//�X�V
	void update(float frameTime,FormCharacter &formCharacter);
	//�`��
	void draw();
	//�|�C���g���ړ�
	void pointMove();
	//��������L�����N�^�[�̎�ނ̌���
	void addFormCharacterType(CharacterType type){ formCharacterTypes.push_back(type); }
	//�񂲂Ƃ̃��X�g�ɒǉ�
	void addColumnCharacters(Character* character);
	
	//List�̎擾
	list<Character*>getFormCharacters(){ return formCharacters; }
	list<Character*>getFirstColumnCharacters(){ return firstColumnCharacters; }
	list<Character*>getSecondColumnCharacters(){ return secondColumnCharacters; }
	list<Character*>getThirdColumnCharacters(){ return thirdColumnCharacters; }
};

#endif