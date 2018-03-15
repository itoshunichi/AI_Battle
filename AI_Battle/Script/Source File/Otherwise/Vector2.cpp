#include"../../Header File/Otherwise/vector2.h"
#include<cmath>

Vector2 vector2(float x, float y)
{
	Vector2 result = { x, y };
	return result;
}

//���ς����߂�
float dot(const Vector2& v1, const Vector2& v2)
{
	return v1.x*v2.x + v1.y*v2.y;
}

//�m���������߂�
float length(const Vector2& v)
{
	return (float)std::sqrt(dot(v, v));
}

//���K������
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

//2�_�Ԃ̋��������߂�
float Distance(const Vector2& my, const Vector2& target)
{
	return length(target - my);
}

//�^�[�Q�b�g�����ւ̈ړ��ʂ����߂�
Vector2 velocity(const Vector2& my, const Vector2& target)
{
	return normalize(target - my);

}

//�w������ւ̈ړ��ʂ����߂�
Vector2 velocity(float angle)
{
	return vector2(Math::cos(angle), Math::sin(angle));
}

//�x�N�g���̌����Ă�p�x�����߂�
float angle(const Vector2& v)
{
	return Math::atan(v.y, v.x);
}

//�^�[�Q�b�g�����ւ̊p�x�����߂�
float angle(const Vector2& my, const Vector2& target)
{
	return angle(target - my);
}

//��̃x�N�g���̂Ȃ��p�x�����߂�
float innerAngle(const Vector2& a, const Vector2& b)
{
	return Math::acos(dot(normalize(a), normalize(b)));
}

//�x�N�g���̐��`���
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

//�p�x�̐��K��
float normalizeAngle(float angle)
{
	return Math::fmod(angle, 360.0f);
}

//�p�x�����߂�
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

//�^�[�Q�b�g�����ւ̊p�x�������߂�
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



