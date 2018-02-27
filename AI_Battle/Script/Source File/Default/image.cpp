#include"../../Header File/Default/image.h"

Image::Image()
{
	initialized = false;            
	spriteData.width = 2;
	spriteData.height = 2;
	spriteData.x = 0.0;
	spriteData.y = 0.0;
	spriteData.scale = 1.0;
	spriteData.angle = 0.0;
	spriteData.rect.left = 0;       
	spriteData.rect.top = 0;
	spriteData.rect.right = spriteData.width;
	spriteData.rect.bottom = spriteData.height;
	spriteData.texture = NULL;     
	spriteData.flipHorizontal = false;
	spriteData.flipVertical = false;
	cols = 1;
	textureManager = NULL;
	startFrame = 0;
	endFrame = 0;
	currentFrame = 0;
	frameDelay = 1.0;               
	animTimer = 0.0;
	visible = true;                 
	loop = true;                    
	animComplete = false;
	graphics = NULL;                
	colorFilter = graphicsNS::WHITE; 

}

Image::~Image()
{

}

//Image��������
//���s��F���������ꍇ��true�A���s�����ꍇ��false��߂�
//Graphics�ւ̃|�C���^
//Image�̕�(�s�N�Z���P��)(0 = �e�N�X�`���S�̂̕����g�p)
//Image�̕�(�s�N�Z���P��)(0 = �e�N�X�`���S�̂̍������g�p)
//�e�N�X�`�����̗�(1����n�܂�)(0�͂P�Ɠ���)
//TextureManager�ւ̃|�C���^
bool Image::initialize(Graphics *g, int width, int heigh, int ncols, TextureManager *textureM)
{
	try{
		graphics = g;  //graphics�I�u�W�F�N�g
		textureManager = textureM; //�e�N�X�`���I�u�W�F�N�g�ւ̃|�C���^
		spriteData.texture = textureManager->getTexture();
		if (width == 0)
			width = textureManager->getWidth(); //�S�̂̕����g�p
		spriteData.width = width;
		if (heigh == 0)
			heigh = textureManager->getHeight();//�S�̂̍������g�p
		spriteData.height = heigh;
		cols = ncols;
		if (cols == 0)
			cols = 1;      //cols���O�̏ꍇ�́A�P���g�p
		//currentFrame��`�悷��spriteDate.rect���\��
		spriteData.rect.left = (currentFrame % cols) * spriteData.width;
		//�E�[+1
		spriteData.rect.right = spriteData.rect.left + spriteData.width;
		spriteData.rect.top = (currentFrame / cols) * spriteData.height;
		//���[+1
		spriteData.rect.bottom = spriteData.rect.top + spriteData.height;
	}
	catch (...){ return false; }
	initialized = true;    
	return true;   
}

//color���t�B���^�Ƃ��Ďg���ĉ摜��`��
//color�p�����[�^�̓I�v�V����
//(image.h�ŁA�f�t�H���g�Ƃ��Ĕ������蓖�Ă��Ă���)
//���s�O�FspriteBegin()���Ăяo��
//���s��:spriteEnd()���Ăяo��
void Image::draw(COLOR_ARGB color)
{
	if (!visible || graphics == NULL)
		return;
	//onReset()���Ăяo���ꂽ�Ƃ��ɐV�����e�N�X�`�����擾
	spriteData.texture = textureManager->getTexture();
	if (color == graphicsNS::FILTER) //�t�B���^���g���ĕ`�悷��ꍇ
		//colorFilter���g�p
		graphics->drawSprite(spriteData, colorFilter);
	else
		//�t�B���^�Ƃ���color���g�p
		graphics->drawSprite(spriteData, color);
}

//�w�肳�ꂽSpriteDate���g���Ă��̉摜��`��
//���݂�SpriteData.rect���g���āA�e�N�X�`�����g�p
//���s�O�FspriteBegin()���Ăяo��
//���s��:spriteEnd()���Ăяo��
void Image::draw(SpriteData sd, COLOR_ARGB color)
{
	if (!visible || graphics == NULL)
		return;
	//���̉摜�̒Z�Y���g���ăe�N�X�`����I��
	sd.rect = spriteData.rect;
	//onReset()���Ăяo���ꂽ�Ƃ��ɐV�����e�N�X�`�����擾
	if (color == graphicsNS::FILTER)  //�t�B���^���g���ĕ`�悷��ꍇ
		graphics->drawSprite(sd, colorFilter);//colorFilter���g�p
	else
		graphics->drawSprite(sd, color);  //�t�B���^�Ƃ���color���g�p
}

//Update
//�ʏ�A�t���[�����ƂɂP��Ăяo��
//frameTime�́A�ړ��ƃA�j���[�V�����̑����𐧌䂷�邽�߂Ɏg�p
void Image::update(float frameTime)
{
	if (endFrame - startFrame > 0) //�A�j���[�V����������X�v���C�g�̏ꍇ
	{
		animTimer += frameTime;  //���v�̌o�ߎ���
		if (animTimer > frameDelay)
		{
			animTimer -= frameDelay;
			currentFrame++;
			if (currentFrame < startFrame || currentFrame > endFrame)
			{
				if (loop == true)     //���[�v����A�j���[�V�����̏ꍇ
					currentFrame = startFrame;
				else //���[�v���Ȃ��A�j���[�V�����̏ꍇ
				{
					currentFrame = endFrame;
					animComplete = true;//�A�j���[�V�����̊���
				}
			}
			setRect();//spriteData.rect��ݒ�
		}

	}

}

//�摜�̌��݂̃t���[����ݒ�
void Image::setCurrentFrame(int c)
{
	if (c >= 0)
	{
		currentFrame = c;
		animComplete = false;
		setRect();                          
	}
}

//currentFrame��`�悷��spriteDate.rect��ݒ�
inline void Image::setRect()
{
	//currentFrame��`�悷��spriteDate.rect���\��
	spriteData.rect.left = (currentFrame % cols) * spriteData.width;
	//�E�[+1
	spriteData.rect.right = spriteData.rect.left + spriteData.width;
	spriteData.rect.top = (currentFrame / cols) * spriteData.height;
	//���[+1
	spriteData.rect.bottom = spriteData.rect.top + spriteData.height;
}

