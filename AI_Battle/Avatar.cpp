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

/*������*/
void Avater::initialize()
{
	position = vector2(10, 0);
	setImage();
	setAnimation();
	currentImage = wait_Image;
}

/*�X�V*/
void Avater::update(float frameTime)
{
	lerpMove.update(frameTime);
	animationUpdate(frameTime);
	currentImage.setX(position.x);
	currentImage.setY(position.y);
	currentImage.setScale(0.5f);
	attack();
}

/*�`��*/
void Avater::draw()
{
	currentImage.draw();
}

//�U���J�n
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

//�v���C���[�̕�������
void Avater::setAngle_ToPlayer(Vector2 playerPos)
{
	float toPlayerAngle = angle(position,playerPos) + 90;
	currentImage.setDegress(toPlayerAngle);
}

/*Image�̐ݒ�*/
void Avater::setImage()
{
	wait_Image = imageManager->GetPlayer_Wait_Image();
}

/*Animation�̐ݒ�*/
void Avater::setAnimation()
{
	//�A�j���[�V�����ݒ�
	wait_Image.setFrames(0, 3);
	wait_Image.setCurrentFrame(0);
	wait_Image.setFrameDlay(0.05);
	wait_Image.setLoop(true);
}

/*�A�j���[�V�����̍X�V*/
void Avater::animationUpdate(float frameTime)
{
	currentImage.update(frameTime);
}






