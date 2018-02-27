#ifndef _TEXTUREMANAGER_H       
#define _TEXTUREMANAGER_H       
#define WIN32_LEAN_AND_MEAN

#include "graphics.h"
#include "constants.h"

using namespace std;

class TextureManager
{
private:
	const char* name;
	UINT width;
	UINT height;
	LP_TEXTURE texture;
	const char *file;
	Graphics *graphics;
	bool initialized;
	HRESULT hr;

public:
	TextureManager();//�R���X�g���N�^
	TextureManager(const char name[]);
	virtual ~TextureManager();//�f�X�g���N�^
	//�e�N�X�`���ւ̃|�C���g��߂�
	LP_TEXTURE getTexture()const{ return texture; }
	//�e�N�X�`���̕���߂�
	UINT getWidth()const { return width; }
	//�e�N�X�`���̍�����߂�
	UINT getHeight()const { return height; }

	bool initialize(Graphics *g);
	//�O���t�B�b�N�X�f�o�C�X���������ꂽ�Ƃ��ɌĂяo�����
	void onLostDevice();
	//�O���t�B�b�N�X�f�o�C�X�����Z�b�g���ꂽ�Ƃ��ɌĂяo�����
	void onResetDevice();

	const char* getName(){ return name; }
};
#endif