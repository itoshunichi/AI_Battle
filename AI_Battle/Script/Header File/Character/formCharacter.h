#ifndef FORMCHARACTER_H_
#define FORMCHARACTER_H_

#include"../GameManager/gameManager.h"
#include"../Default/entity.h"
#include"../Otherwise/math.h"
#include"../Character/character.h"
#include"testCharacter.h"
#include"longAttackTestCharacter.h"
#include"testAirCharacter.h"
#include"characterType.h"
#include"../Otherwise/timer.h"
#include"characterCost.h"
#include"playerNum.h"
#include"characterCostManager.h"

//�L�����N�^�[�𐶐�����N���X
class FormCharacter
{
private:
	GameManager *gameManager;
	CharacterCostManager characterCost;
	Input *input;
	//�����|�C���g�̉摜
	Image pointImage;
	//�����|�C���g�̍��W
	Vector2 pointPosition;
	PlayerNum playerNum;
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
	//�L�����N�^�[�̍폜
	void removeCharacter();
	//1P���ǂ���
	bool isPlayer1(){ return playerNum == PlayerNum::PLAYER1; }
	//2P���ǂ���
	bool isPlayer2(){ return playerNum ==PlayerNum::PLAYER2; }
	//�����Ŏw�肵���񂩂ǂ���
	bool isCurrentRow(int curretRow){ return this->currentRow == currentRow; }
public:
	FormCharacter();
	FormCharacter(GameManager *gameManager,PlayerNum playerNum);
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