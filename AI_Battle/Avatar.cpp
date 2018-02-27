#include"avater.h"

Avater::Avater()
{

}

Avater::Avater(GameManager *gameManager)
{
	this->gameManager = gameManager;
	this->imageManager = gameManager->getImageManager();
	initialize();
}

Avater::~Avater()
{

}

/*初期化*/
void Avater::initialize()
{
	position = vector2(10, 0);
	setImage();
	setAnimation();
	currentImage = wait_Image;
}

/*更新*/
void Avater::update(float frameTime)
{
	lerpMove.update(frameTime);
	animationUpdate(frameTime);
	currentImage.setX(position.x);
	currentImage.setY(position.y);
	currentImage.setScale(0.5f);
	attack();
}

/*描画*/
void Avater::draw()
{
	currentImage.draw();
}

//攻撃開始
void Avater::startAttack(Vector2 endPos)
{
	lerpMove.startMove(position, endPos, 0.1f);
	isAttack = true;

}

void Avater::attack()
{
	if (isAttack)
	{
		lerpMove.movePosition(&position);
		if (lerpMove.IsEnd())
		{
			isAttack = false;
		}
	}
}

//プレイヤーの方を向く
void Avater::setAngle_ToPlayer(Vector2 playerPos)
{
	float toPlayerAngle = angle(position,playerPos) + 90;
	currentImage.setDegress(toPlayerAngle);
}

/*Imageの設定*/
void Avater::setImage()
{
	wait_Image = imageManager->GetPlayer_Wait_Image();
}

/*Animationの設定*/
void Avater::setAnimation()
{
	//アニメーション設定
	wait_Image.setFrames(0, 3);
	wait_Image.setCurrentFrame(0);
	wait_Image.setFrameDlay(0.05);
	wait_Image.setLoop(true);
}

/*アニメーションの更新*/
void Avater::animationUpdate(float frameTime)
{
	currentImage.update(frameTime);
}






