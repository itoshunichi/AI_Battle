#ifndef AVATER_H_
#define AVATER_H_

#include"gameManager.h"
#include"vector2.h"
#include"lerpMove.h"
#include"entity.h"


class Avater:public Entity
{
	//変数
private:
	//ゲームマネージャー
	//GameManager *gameManager;
	//ImageManager *imageManager;
	//移動速度
	float speed;
	//現在の画像
	//Image currentImage;
	//各画像
	Image wait_Image;
	//移動時の目標位置
	Vector2 move_TargetPosition;
	LerpMove lerpMove;
	bool isAttack = false;


public:
	Avater();
	Avater(GameManager *gameManager);
	~Avater();
	//初期化
	void initialize();
	//更新
	void update(float frameTime);
	//描画
	void draw();
	//プレイヤーの方を向く
	void setAngle_ToPlayer(Vector2 playerPos);
	//攻撃開始
	void startAttack(Vector2 endPos);
	//攻撃処理
	void attack();

	void setAngle(float angle){ currentImage.setDegress(angle); }
	

private:
	//Imageの設定
	void setImage();
	//アニメーションの設定
	void setAnimation();
	//アニメーションの更新
	void animationUpdate(float frameTime);
};

#endif