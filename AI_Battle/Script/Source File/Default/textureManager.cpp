#include "../../Header File/Default/textureManager.h"

TextureManager::TextureManager()
{
	texture = NULL;
	width = 0;
	height = 0;
	file = NULL;
	graphics = NULL;
	initialized = false;
}

TextureManager::TextureManager(const char *name)
{
	this->name = name;
	texture = NULL;
	width = 0;
	height = 0;
	file = NULL;
	graphics = NULL;
	initialized = false;
}

TextureManager::~TextureManager()
{
	SAFE_RELEASE(texture);
}

//�e�N�X�`���t�@�C�����f�B�X�N����ǂݍ���
//���s��:���������ꍇ��true,���s�����ꍇ��false��߂�
bool TextureManager::initialize(Graphics *g)
{
	try{
		graphics = g;
		file = name;
		hr = graphics->loadTexture(
			file, TRANSCOLOR, width, height, texture);
		if (FAILED(hr))
		{
			SAFE_RELEASE(texture);
			return false;
		}
	}

	catch (...){ return false; }
	initialized = true; //����ɏ��������ꂽ�ꍇ�Atrue
	return true;
}



//�O���t�B�b�N�X�f�o�C�X�����������Ƃ��ɌĂяo�����
void TextureManager::onLostDevice()
{
	if (!initialized)
		return;
	SAFE_RELEASE(texture);
}

//�O���t�B�b�N�X�f�o�C�X�����Z�b�g���ꂽ�Ƃ��ɌĂяo�����
void TextureManager::onResetDevice()
{
	if (!initialized)
		return;
	graphics->loadTexture(file, TRANSCOLOR, width, height, texture);
}