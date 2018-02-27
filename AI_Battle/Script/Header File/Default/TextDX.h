#ifndef _TEXTDX_H
#define _TEXTDX_H
#define WIN32_LEAN_AND_MEAN

#include<string>
#include"constants.h"
#include"graphics.h"

class TextDX
{
private:
	Graphics *graphics;
	COLOR_ARGB color;
	LP_DXFONT dxFont;
	RECT fontRect;
	D3DXMATRIX matrix;
	float angle;

public:
	TextDX();
	virtual ~TextDX();
	virtual bool initialize(Graphics *g, int height, bool bold, bool italic, const std::string &fontName);
	//テキストをx,yに出力
	virtual int print(const std::string &str, int x, int y);
	//DirectXテキスト書式を使って、RECT内にテキストを出力
	virtual int print(const std::string &str, RECT &rect, UINT format);
	virtual float getDegrees()      { return angle*(180.0f / (float)PI); }
	virtual float getRadians()      { return angle; }
	virtual COLOR_ARGB getFontColor() { return color; }
	virtual void setDegrees(float deg)  { angle = deg*((float)PI / 180.0f); }
	virtual void setRadians(float rad)  { angle = rad; }
	virtual void setFontColor(COLOR_ARGB c) { color = c; }
	virtual void onLostDevice();
	virtual void onResetDevice();
};

#endif