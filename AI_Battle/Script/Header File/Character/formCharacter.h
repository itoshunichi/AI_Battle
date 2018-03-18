#ifndef FORMCHARACTER_H_
#define FORMCHARACTER_H_

#include"../GameManager/gameManager.h"
#include"../Default/entity.h"
#include"../Otherwise/math.h"
#include"../Character/character.h"
#include"testCharacter.h"
#include"longAttackTestCharacter.h"
#include"characterType.h"

//キャラクターを生成するクラス
class FormCharacter
{
private:
	GameManager *gameManager;
	Input *input;
	//生成ポイントの画像
	Image pointImage;
	//生成ポイントの座標
	Vector2 pointPosition;
	int playerNum;
	Entity myShop;
	//生成するキャラクターのリスト
	vector<CharacterType>formCharacterTypes;
	//自分がいまどこの列にいるか
	int currentRow;
	//生成するキャラクターのリスト
	list<Character*>formCharacters;
	//1列目のキャラ
	list<Character*>firstColumnCharacters;
	//2列目のキャラ
	list<Character*>secondColumnCharacters;
	//3列目のキャラ
	list<Character*>thirdColumnCharacters;

private:
	void formSelectCharacter(CharacterType type);
	void formCharacter();
	//現在いるの列を設定
	void setCurrentRow();
	//生成する位置
	Vector2 formPosition();
	//キャラクターの削除
	void removeCharacter();
public:
	FormCharacter();
	FormCharacter(GameManager *gameManager,Entity &myShop,int playerNum);
	~FormCharacter();
	//初期化
	void initalize();
	//更新
	void update(float frameTime,FormCharacter &formCharacter);
	//描画
	void draw();
	//ポイントも移動
	void pointMove();
	//生成するキャラクターの種類の決定
	void addFormCharacterType(CharacterType type){ formCharacterTypes.push_back(type); }
	//列ごとのリストに追加
	void addColumnCharacters(Character* character);
	
	//Listの取得
	list<Character*>getFormCharacters(){ return formCharacters; }
	list<Character*>getFirstColumnCharacters(){ return firstColumnCharacters; }
	list<Character*>getSecondColumnCharacters(){ return secondColumnCharacters; }
	list<Character*>getThirdColumnCharacters(){ return thirdColumnCharacters; }
};

#endif