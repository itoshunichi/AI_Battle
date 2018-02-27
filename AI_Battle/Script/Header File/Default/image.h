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
	//colorフィルタとして使って画像を描画。colorのデフォルトは白
	void draw(COLOR_ARGB color = graphicsNS::WHITE);
	//指定されたSpriteDataを使ってこの画像を描画
	void draw(SpriteData sd, COLOR_ARGB color = graphicsNS::WHITE);
	//画像を水平方向に反転(鏡)
	virtual void flipHorizontal(bool flip){ spriteData.flipHorizontal = flip; }
	//画像を垂直方向に反転
	virtual  void flipVertical(bool flip){ spriteData.flipVertical = flip; }

	//SpriteDate構造体への参照を戻す
	const virtual SpriteData& getSpriteInfo(){ return spriteData; }
	//visibleパラメータを戻す
	virtual bool getVisible(){ return visible; }
	//X位置を戻す
	virtual float getX(){ return spriteData.x; }
	//Y位置をも戻す
	virtual float getY(){ return spriteData.y; }
	//倍率を戻す
	virtual float getScale(){ return spriteData.scale; }
	//幅を戻す
	virtual int getWidth(){ return spriteData.width; }
	//高さを戻す
	virtual int getHeight(){ return spriteData.height; }
	//中心点のXを戻す
	virtual float getCenterX(){ return spriteData.x + spriteData.width / 2 * getScale(); }
	//中心点のYを戻す
	virtual float getCenterY(){ return spriteData.y + spriteData.height / 2 * getScale(); }
	//回転角度(度単位)を戻す
	virtual float getDegress(){ return spriteData.angle*(180.0f / (float)PI); }
	//回転角度(ラジアン単位)を戻す
	virtual float getRadians(){ return spriteData.angle; }
	//アニメーションのフレーム間の間隔を戻す
	virtual float getFrameDelay(){ return frameDelay; }
	//開始フレームの番号を戻す
	virtual int getStartFrame(){ return startFrame; }
	//終了フレームの番号を戻す
	virtual int getEndFrame(){ return endFrame; }
	//現在のフレームの番号を戻す
	virtual int getCurrentFrame(){ return currentFrame; }
	//ImageのRECT構造体を戻す
	virtual RECT getSpriteDateRect(){ return spriteData.rect; }
	//アニメーション完了の状態を戻す
	virtual bool getAnimationComplete(){ return animComplete; }
	//colorFilterを戻す
	virtual COLOR_ARGB getColorFilter(){ return colorFilter; }

	//X位置を設定
	virtual void setX(float newX){ spriteData.x = newX; }
	//Y位置を設定
	virtual void setY(float newY){ spriteData.y = newY; }
	//拡大縮小を設定
	virtual void setScale(float s){ spriteData.scale = s; }
	//回転角度を設定(度単位)
	//0度は上向きです。角度は時計回りに進みます
	virtual void setDegress(float deg){ spriteData.angle = deg*((float)PI / 180.0f); }
	//回転角度を設定(ラジアン単位)
	//0ラジアンは上向きです。角度は時計回りに進みます
	virtual void setRadians(float rad){ spriteData.angle = rad; }
	//可視性を設定
	virtual void setVisible(bool v){ visible = v; }
	//アニメーションのフレーム間の間隔を設定
	virtual void setFrameDlay(float d){ frameDelay = d; }
	//アニメーションの開始フレームと終了フレームを設定
	virtual void setFrames(int s, int e){ startFrame = s; endFrame = e; }
	//アニメーションの現在のフレームを設定
	virtual void setCurrentFrame(int c);
	//currentFrameを描画するspriteDate.rectを設定
	virtual void setRect();
	//spriteDate.rectをrに設定
	virtual void setSpriteDateRect(RECT r){ spriteData.rect = r; }
	//アニメーションループを設定(lp = trueの場合にループする)
	virtual void setLoop(bool lp){ loop = lp; }
	//アニメーション完了ブール値を設定
	virtual void setAnimationComplete(bool a){ animComplete = a; }
	//色フィルタを設定(WHITEを使用すると、変化しない)
	virtual void setColorFilter(COLOR_ARGB color){ colorFilter = color; }
	virtual SpriteData getSpriteDate(){ return spriteData; }

	void update(float frameTime);




};
#endif



