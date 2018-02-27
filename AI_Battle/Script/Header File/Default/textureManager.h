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
	TextureManager();//コンストラクタ
	TextureManager(const char name[]);
	virtual ~TextureManager();//デストラクタ
	//テクスチャへのポイントを戻す
	LP_TEXTURE getTexture()const{ return texture; }
	//テクスチャの幅を戻す
	UINT getWidth()const { return width; }
	//テクスチャの高さを戻す
	UINT getHeight()const { return height; }

	bool initialize(Graphics *g);
	//グラフィックスデバイスが消失されたときに呼び出される
	void onLostDevice();
	//グラフィックスデバイスがリセットされたときに呼び出される
	void onResetDevice();

	const char* getName(){ return name; }
};
#endif