#include<cmath>

#include"../../Header File/Otherwise/math.h"
//#include"math.h"
#include<algorithm>


const float Math::PI = 3.1415926535897932f;

float Math::sin(float degree)
{
	return (float)std::sin(radian(degree));
}

float Math::cos(float degree)
{
	return (float)std::cos(radian(degree));
}

float Math::tan(float degree)
{
	return (float)std::tan(radian(degree));
}

float Math::asin(float x)
{
	return degree((float)std::asin(x));
}

float Math::acos(float x)
{
	return degree((float)std::acos(x));
}

float Math::atan(float y, float x)
{
	return degree((float)std::atan2(y, x));
}

float Math::radian(float degree)
{
	return degree*(PI / 180.0f);
}

float Math::degree(float radian)
{
	return radian*(180.0 / PI);
}

float Math::fmod(float x, float y)
{
	return std::fmod(x, y);
}

float Math::clamp(float x, float min, float max)
{
	return std::min(std::max(min, x), max);
}

float Math::abs(float num)
{
	return std::abs(num);
}

float Math::Min(float num, float nimNum)
{
	return std::min(num, nimNum);
}

float Math::Max(float num, float maxNum)
{
	return std::max(num, maxNum);
}