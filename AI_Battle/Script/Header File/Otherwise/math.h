#ifndef _MATH_UTILITY_H_
#define _MATH_UTILITY_H_

class Math
{
public:
	//円周率
	static const float PI;

	//サイン
	static float sin(float degree);
	//コサイン
	static float cos(float degree);
	//タンジェント
	static float tan(float degree);

	//逆サイン
	static float asin(float x);
	//逆コサイン
	static float acos(float x);
	//逆タンジェント
	static float atan(float y, float x);

	//角度をラジアンに変換
	static float radian(float degree);
	//ラジアンを角度に変換
	static float degree(float radian);

	static float fmod(float x, float y);

	static float clamp(float x, float min, float max);

	static float abs(float num);

	static float Min(float num, float minNum);

	static float Max(float num,float maxNum);
};
#endif