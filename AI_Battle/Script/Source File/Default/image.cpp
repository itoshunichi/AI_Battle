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

//Imageを初期化
//実行後：成功した場合はtrue、失敗した場合はfalseを戻す
//Graphicsへのポインタ
//Imageの幅(ピクセル単位)(0 = テクスチャ全体の幅を使用)
//Imageの幅(ピクセル単位)(0 = テクスチャ全体の高さを使用)
//テクスチャ内の列数(1からnまで)(0は１と同じ)
//TextureManagerへのポインタ
bool Image::initialize(Graphics *g, int width, int heigh, int ncols, TextureManager *textureM)
{
	try{
		graphics = g;  //graphicsオブジェクト
		textureManager = textureM; //テクスチャオブジェクトへのポインタ
		spriteData.texture = textureManager->getTexture();
		if (width == 0)
			width = textureManager->getWidth(); //全体の幅を使用
		spriteData.width = width;
		if (heigh == 0)
			heigh = textureManager->getHeight();//全体の高さを使用
		spriteData.height = heigh;
		cols = ncols;
		if (cols == 0)
			cols = 1;      //colsが０の場合は、１を使用
		//currentFrameを描画するspriteDate.rectを構成
		spriteData.rect.left = (currentFrame % cols) * spriteData.width;
		//右端+1
		spriteData.rect.right = spriteData.rect.left + spriteData.width;
		spriteData.rect.top = (currentFrame / cols) * spriteData.height;
		//下端+1
		spriteData.rect.bottom = spriteData.rect.top + spriteData.height;
	}
	catch (...){ return false; }
	initialized = true;    
	return true;   
}

//colorをフィルタとして使って画像を描画
//colorパラメータはオプション
//(image.hで、デフォルトとして白が割り当てられている)
//実行前：spriteBegin()を呼び出す
//実行後:spriteEnd()を呼び出す
void Image::draw(COLOR_ARGB color)
{
	if (!visible || graphics == NULL)
		return;
	//onReset()が呼び出されたときに新しいテクスチャを取得
	spriteData.texture = textureManager->getTexture();
	if (color == graphicsNS::FILTER) //フィルタを使って描画する場合
		//colorFilterを使用
		graphics->drawSprite(spriteData, colorFilter);
	else
		//フィルタとしてcolorを使用
		graphics->drawSprite(spriteData, color);
}

//指定されたSpriteDateを使ってこの画像を描画
//現在のSpriteData.rectを使って、テクスチャを使用
//実行前：spriteBegin()を呼び出す
//実行後:spriteEnd()を呼び出す
void Image::draw(SpriteData sd, COLOR_ARGB color)
{
	if (!visible || graphics == NULL)
		return;
	//この画像の短刑を使ってテクスチャを選択
	sd.rect = spriteData.rect;
	//onReset()が呼び出されたときに新しいテクスチャを取得
	if (color == graphicsNS::FILTER)  //フィルタを使って描画する場合
		graphics->drawSprite(sd, colorFilter);//colorFilterを使用
	else
		graphics->drawSprite(sd, color);  //フィルタとしてcolorを使用
}

//Update
//通常、フレームごとに１回呼び出す
//frameTimeは、移動とアニメーションの速さを制御するために使用
void Image::update(float frameTime)
{
	if (endFrame - startFrame > 0) //アニメーション化するスプライトの場合
	{
		animTimer += frameTime;  //合計の経過時間
		if (animTimer > frameDelay)
		{
			animTimer -= frameDelay;
			currentFrame++;
			if (currentFrame < startFrame || currentFrame > endFrame)
			{
				if (loop == true)     //ループするアニメーションの場合
					currentFrame = startFrame;
				else //ループしないアニメーションの場合
				{
					currentFrame = endFrame;
					animComplete = true;//アニメーションの完了
				}
			}
			setRect();//spriteData.rectを設定
		}

	}

}

//画像の現在のフレームを設定
void Image::setCurrentFrame(int c)
{
	if (c >= 0)
	{
		currentFrame = c;
		animComplete = false;
		setRect();                          
	}
}

//currentFrameを描画するspriteDate.rectを設定
inline void Image::setRect()
{
	//currentFrameを描画するspriteDate.rectを構成
	spriteData.rect.left = (currentFrame % cols) * spriteData.width;
	//右端+1
	spriteData.rect.right = spriteData.rect.left + spriteData.width;
	spriteData.rect.top = (currentFrame / cols) * spriteData.height;
	//下端+1
	spriteData.rect.bottom = spriteData.rect.top + spriteData.height;
}

