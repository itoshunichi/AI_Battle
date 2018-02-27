#ifndef _IMAGE_H                
#define _IMAGE_H                
#define WIN32_LEAN_AND_MEAN

#include "textureManager.h"
#include "constants.h"

class Image
{
protected:
	Graphics *graphics;
	TextureManager *textureManager;
	SpriteData spriteData;
	COLOR_ARGB colorFilter;
	int cols;
	int startFrame;
	int endFrame;
	int currentFrame;
	float frameDelay;
	float animTimer;
	HRESULT hr;
	bool loop;
	bool visible;
	bool initialized;
	bool animComplete;

public:
	Image();
	virtual ~Image();
	bool initialize(Graphics *g, int width, int height, int ncols,
		TextureManager *textureM);
	//color�t�B���^�Ƃ��Ďg���ĉ摜��`��Bcolor�̃f�t�H���g�͔�
	void draw(COLOR_ARGB color = graphicsNS::WHITE);
	//�w�肳�ꂽSpriteData���g���Ă��̉摜��`��
	void draw(SpriteData sd, COLOR_ARGB color = graphicsNS::WHITE);
	//�摜�𐅕������ɔ��](��)
	virtual void flipHorizontal(bool flip){ spriteData.flipHorizontal = flip; }
	//�摜�𐂒������ɔ��]
	virtual  void flipVertical(bool flip){ spriteData.flipVertical = flip; }

	//SpriteDate�\���̂ւ̎Q�Ƃ�߂�
	const virtual SpriteData& getSpriteInfo(){ return spriteData; }
	//visible�p�����[�^��߂�
	virtual bool getVisible(){ return visible; }
	//X�ʒu��߂�
	virtual float getX(){ return spriteData.x; }
	//Y�ʒu�����߂�
	virtual float getY(){ return spriteData.y; }
	//�{����߂�
	virtual float getScale(){ return spriteData.scale; }
	//����߂�
	virtual int getWidth(){ return spriteData.width; }
	//������߂�
	virtual int getHeight(){ return spriteData.height; }
	//���S�_��X��߂�
	virtual float getCenterX(){ return spriteData.x + spriteData.width / 2 * getScale(); }
	//���S�_��Y��߂�
	virtual float getCenterY(){ return spriteData.y + spriteData.height / 2 * getScale(); }
	//��]�p�x(�x�P��)��߂�
	virtual float getDegress(){ return spriteData.angle*(180.0f / (float)PI); }
	//��]�p�x(���W�A���P��)��߂�
	virtual float getRadians(){ return spriteData.angle; }
	//�A�j���[�V�����̃t���[���Ԃ̊Ԋu��߂�
	virtual float getFrameDelay(){ return frameDelay; }
	//�J�n�t���[���̔ԍ���߂�
	virtual int getStartFrame(){ return startFrame; }
	//�I���t���[���̔ԍ���߂�
	virtual int getEndFrame(){ return endFrame; }
	//���݂̃t���[���̔ԍ���߂�
	virtual int getCurrentFrame(){ return currentFrame; }
	//Image��RECT�\���̂�߂�
	virtual RECT getSpriteDateRect(){ return spriteData.rect; }
	//�A�j���[�V���������̏�Ԃ�߂�
	virtual bool getAnimationComplete(){ return animComplete; }
	//colorFilter��߂�
	virtual COLOR_ARGB getColorFilter(){ return colorFilter; }

	//X�ʒu��ݒ�
	virtual void setX(float newX){ spriteData.x = newX; }
	//Y�ʒu��ݒ�
	virtual void setY(float newY){ spriteData.y = newY; }
	//�g��k����ݒ�
	virtual void setScale(float s){ spriteData.scale = s; }
	//��]�p�x��ݒ�(�x�P��)
	//0�x�͏�����ł��B�p�x�͎��v���ɐi�݂܂�
	virtual void setDegress(float deg){ spriteData.angle = deg*((float)PI / 180.0f); }
	//��]�p�x��ݒ�(���W�A���P��)
	//0���W�A���͏�����ł��B�p�x�͎��v���ɐi�݂܂�
	virtual void setRadians(float rad){ spriteData.angle = rad; }
	//������ݒ�
	virtual void setVisible(bool v){ visible = v; }
	//�A�j���[�V�����̃t���[���Ԃ̊Ԋu��ݒ�
	virtual void setFrameDlay(float d){ frameDelay = d; }
	//�A�j���[�V�����̊J�n�t���[���ƏI���t���[����ݒ�
	virtual void setFrames(int s, int e){ startFrame = s; endFrame = e; }
	//�A�j���[�V�����̌��݂̃t���[����ݒ�
	virtual void setCurrentFrame(int c);
	//currentFrame��`�悷��spriteDate.rect��ݒ�
	virtual void setRect();
	//spriteDate.rect��r�ɐݒ�
	virtual void setSpriteDateRect(RECT r){ spriteData.rect = r; }
	//�A�j���[�V�������[�v��ݒ�(lp = true�̏ꍇ�Ƀ��[�v����)
	virtual void setLoop(bool lp){ loop = lp; }
	//�A�j���[�V���������u�[���l��ݒ�
	virtual void setAnimationComplete(bool a){ animComplete = a; }
	//�F�t�B���^��ݒ�(WHITE���g�p����ƁA�ω����Ȃ�)
	virtual void setColorFilter(COLOR_ARGB color){ colorFilter = color; }
	virtual SpriteData getSpriteDate(){ return spriteData; }

	void update(float frameTime);




};
#endif



