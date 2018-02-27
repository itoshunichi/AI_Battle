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

//テクスチャファイルをディスクから読み込む
//実行後:成功した場合はtrue,失敗した場合はfalseを戻す
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
	initialized = true; //正常に初期化された場合、true
	return true;
}



//グラフィックスデバイスが消失したときに呼び出される
void TextureManager::onLostDevice()
{
	if (!initialized)
		return;
	SAFE_RELEASE(texture);
}

//グラフィックスデバイスがリセットされたときに呼び出される
void TextureManager::onResetDevice()
{
	if (!initialized)
		return;
	graphics->loadTexture(file, TRANSCOLOR, width, height, texture);
}