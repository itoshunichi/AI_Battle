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
	//初期位置
	position = VECTOR2(0, 762);
	//初期の向き
	direction = Direction::UP;
	image = gameTexture->getPlayerImage();
	dive_Image = gameTexture->getDivePlayerImage();

	//アニメーション設定
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

//角度の設定
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

//移動
void TitlePlayer::move(float frameTime)
{
	//タイマーの更新
	moveTimer.update(frameTime);
	//タイマーが終わったら
	if (moveTimer.isEnd())
	{
		//移動
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
		//タイマーをリセット
		moveTimer.resetTimer();
	}
}

//向きの変更
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