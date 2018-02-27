#include"titlePlayer.h"

TitlePlayer::TitlePlayer()
{
}

TitlePlayer::TitlePlayer(ImageManager *gameTexture)
{
	this->gameTexture = gameTexture;
}

void TitlePlayer::initialize()
{
	//�����ʒu
	position = VECTOR2(0, 762);
	//�����̌���
	direction = Direction::UP;
	image = gameTexture->getPlayerImage();
	dive_Image = gameTexture->getDivePlayerImage();

	//�A�j���[�V�����ݒ�
	dive_Image.setFrames(0, 8);
	dive_Image.setCurrentFrame(0);
	dive_Image.setFrameDlay(0.03f);
	dive_Image.setLoop(false);

	image.setX(position.x);
	image.setY(position.y);
	isDive = false;
	moveTimer = Timer(0.2f);
	moveTimer.resetTimer();
	//timer = 0;
	//moveTiming = 1.5f;
	
}

void TitlePlayer::draw()
{
	if (isDive)
	{
		dive_Image.draw();
	}
	else
	{
		image.draw();
	}

}

void TitlePlayer::update(float frameTime)
{
	animationUpdate(frameTime);
	setAngle();
	changeDirection();
	move(frameTime);
}

void TitlePlayer::animationUpdate(float frameTime)
{
	if (isDive)
	{
		dive_Image.update(frameTime);
	}
	else
	{
		dive_Image.setX(position.x);
		dive_Image.setY(position.y);
	}

	image.setDegress(angle);
	dive_Image.setDegress(angle);
}

//�p�x�̐ݒ�
void TitlePlayer::setAngle()
{
	if (direction == Direction::UP)
	{
		angle = 0;
	}
	if (direction == Direction::RIGHT)
	{
		angle = 90;
	}
	if (direction == Direction::LEFT)
	{
		angle = 270;
	}
	if (direction == Direction::DOWN)
	{
		angle = 180;
	}
}

//�ړ�
void TitlePlayer::move(float frameTime)
{
	//�^�C�}�[�̍X�V
	moveTimer.update(frameTime);
	//�^�C�}�[���I�������
	if (moveTimer.isEnd())
	{
		//�ړ�
		if (direction == Direction::UP)
		{
			position.y -= image.getWidth();
		}
		else if (direction == Direction::DOWN)
		{
			position.y += image.getWidth();
		}
		else if (direction == Direction::RIGHT)
		{
			position.x += image.getWidth();
		}
		else if (direction == Direction::LEFT)
		{
			position.x -= image.getWidth();
		}
		image.setX(position.x);
		image.setY(position.y);
		//�^�C�}�[�����Z�b�g
		moveTimer.resetTimer();
	}
}

//�����̕ύX
void TitlePlayer::changeDirection()
{
	if (direction == Direction::UP&&position.y <0)
	{
		direction = Direction::RIGHT;
	}
	if (direction == Direction::RIGHT&&position.x == 1280 - image.getWidth())
	{
		direction = Direction::DOWN;
	}
	if (direction == Direction::DOWN&&position.y == 762 - image.getWidth())
	{
		direction = Direction::LEFT;
	}
	if (direction == Direction::LEFT&&position.x == 0)
	{
		direction = Direction::UP;
	}
}