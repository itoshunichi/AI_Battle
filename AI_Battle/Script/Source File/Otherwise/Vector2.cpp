#include"../../Header File/Otherwise/vector2.h"
#include<cmath>

Vector2 vector2(float x, float y)
{
	Vector2 result = { x, y };
	return result;
}

//内積を求める
float dot(const Vector2& v1, const Vector2& v2)
{
	return v1.x*v2.x + v1.y*v2.y;
}

//ノルムを求める
float length(const Vector2& v)
{
	return (float)std::sqrt(dot(v, v));
}

//正規化する
Vector2 normalize(const Vector2& v)
{
	Vector2 result = v;
	float len = length(result);
	if (len != 0)
	{
		result /= len;
	}
	return result;
}

//2点間の距離を求める
float Distance(const Vector2& my, const Vector2& target)
{
	return length(target - my);
}

//ターゲット方向への移動量を求める
Vector2 velocity(const Vector2& my, const Vector2& target)
{
	return normalize(target - my);

}

//指定方向への移動量を求める
Vector2 velocity(float angle)
{
	return vector2(Math::cos(angle), Math::sin(angle));
}

//ベクトルの向いてる角度を求める
float angle(const Vector2& v)
{
	return Math::atan(v.y, v.x);
}

//ターゲット方向への角度を求める
float angle(const Vector2& my, const Vector2& target)
{
	return angle(target - my);
}

//二つのベクトルのなす角度を求める
float innerAngle(const Vector2& a, const Vector2& b)
{
	return Math::acos(dot(normalize(a), normalize(b)));
}

//ベクトルの線形補間
Vector2 lerp(const Vector2& start, const Vector2& end, float t)
{
	if (t < 0.0f)
	{
		t = 0.0f;
	}
	else if (t>1.0f)
	{
		t = 1.0f;
	}
	return start *(1.0f - t) + end*t;
}

//角度の正規化
float normalizeAngle(float angle)
{
	return Math::fmod(angle, 360.0f);
}

//角度を求める
float subtractAngle(float my, float target)
{
	float d = normalizeAngle(target - my);
	if (d > 180.0f){
		d -= 360.0f;
	}
	else if (d < -180.0f){
		d += 360.0f;
	}
	return d;
}

Vector2 middlePoint(Vector2 v1, Vector2 v2)
{
	return vector2((v1.x + v2.x) / 2, (v1.y + v2.y) / 2);
}

//ターゲット方向への角度差を求める
float subtractAngle(const Vector2& my, float dir, const Vector2& target)
{
	return subtractAngle(dir, angle(my, target));
}

Vector2 operator +(const Vector2& v)
{
	return v;
}

Vector2 operator -(const Vector2& v)
{
	Vector2 result = { -v.x, -v.y };
	return result;
}

Vector2& operator +=(Vector2& v1, const Vector2& v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
	return v1;
}

Vector2& operator -=(Vector2& v1, const Vector2& v2)
{
	v1.x -= v2.x;
	v1.y -= v2.y;
	return v1;
}

Vector2& operator *=(Vector2& v, float s)
{
	v.x *= s;
	v.y *= s;
	return v;
}

Vector2& operator/=(Vector2& v, float s)
{
	v *= 1.0f / s;
	return v;
}

Vector2 operator+(const Vector2& v1, const Vector2& v2)
{
	Vector2 result = v1;
	return result += v2;
}

Vector2 operator-(const Vector2& v1, const Vector2& v2)
{
	Vector2 result = v1;
	return result -= v2;
}

Vector2 operator *(const Vector2& v, float s)
{
	Vector2 result = v;
	return result *= s;
}

Vector2 operator *(float s, const Vector2& v)
{
	Vector2 result = v;
	return result *= s;
}

Vector2 operator /(const Vector2& v, float s)
{
	Vector2 result = v;
	return result / s;
}



