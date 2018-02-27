#include"../../Header File/Otherwise/Fade.h"

Fade::Fade()
{
	
}
Fade::Fade(ImageManager *gameTexture)
{
	this->gameTexture = gameTexture;
}



void Fade::initialize()
{
	image = gameTexture->getFadeImage();
	alpha = 255;
	isEnd = false;
	mode = Mode::FADEIN;
}

void Fade::update()
{
	if (mode == Mode::FADEIN)
	{
		if (alpha > 0)
		{
			alpha--;
		}
	}

	if (mode == Mode::FADEOUT)
	{
		if (alpha < 255)
		{
			alpha++;
		}
		if (alpha == 255)
		{
			isEnd = true;
		}
	}
}

void Fade::draw()
{
	image.draw(image.getSpriteDate(), D3DCOLOR_ARGB(alpha, 255, 255, 255)&graphicsNS::WHITE);
}



void Fade::fadeOutStart()
{
	mode = Mode::FADEOUT;
}