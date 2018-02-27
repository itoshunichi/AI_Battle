#ifndef _VECTOR2_H_
#define _VECTOR2_H_

#include"math.h"

//2次元ベクトル型
struct Vector2
{
	float x;//X成分
	float y;//Y成分
};

//2Dベクトルを作成
Vector2 vector2(float x, float y);
//内積を求める
float dot(const Vector2& v1, const Vector2& v2);
//ノルムを求める
float length(const Vector2& v);
//正規化する 
Vector2 normalize(const Vector2& v);
//2点間の距離を求める
float distance(const Vector2&my, const Vector2& target);
//ターゲット方向への移動量を求める
Vector2 velocity(const Vector2& my, const Vector2& targetf);
//指定方向への移動量を求める
Vector2 velocity(float angle);
//ベクトルの向いてる角度を求める
float angle(const Vector2& v);
//ターゲット方向への角度を求める
float angle(const Vector2& my, const Vector2& target);
//二つのベクトルのなす角度を求める
float innerAngle(const Vector2& a, const Vector2& b);
//ベクトルの線形補間
Vector2 lerp(const Vector2& start, const Vector2& end, float t);
//ターゲット方向への角度差を求める
float subtractAngle(const Vector2& my, float dir, const Vector2& target);
//二つの点の中点を求める
Vector2 middlePoint(Vector2 v1, Vector2 v2);

//単項演算子オーバーロード
Vector2 operator+(const Vector2& v);
Vector2 operator-(const Vector2& v);

//代入演算子オーバーロード
Vector2& operator +=(Vector2& v1, const Vector2& v2);
Vector2& operator -=(Vector2& v1, const Vector2& v2);
Vector2& operator *=(Vector2& v, float s);
Vector2& operator /=(Vector2& v, float s);

//2項演算子オーバーロード
Vector2 operator +(const Vector2& v1, const Vector2& v2);
Vector2 operator -(const Vector2& v1, const Vector2& v2);
Vector2 operator*(const Vector2& v, float s);
Vector2 operator*(float s, const Vector2& v);
Vector2 operator/(const Vector2& v, float s);

#endif
