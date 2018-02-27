#ifndef _VECTOR2_H_
#define _VECTOR2_H_

#include"math.h"

//2�����x�N�g���^
struct Vector2
{
	float x;//X����
	float y;//Y����
};

//2D�x�N�g�����쐬
Vector2 vector2(float x, float y);
//���ς����߂�
float dot(const Vector2& v1, const Vector2& v2);
//�m���������߂�
float length(const Vector2& v);
//���K������ 
Vector2 normalize(const Vector2& v);
//2�_�Ԃ̋��������߂�
float distance(const Vector2&my, const Vector2& target);
//�^�[�Q�b�g�����ւ̈ړ��ʂ����߂�
Vector2 velocity(const Vector2& my, const Vector2& targetf);
//�w������ւ̈ړ��ʂ����߂�
Vector2 velocity(float angle);
//�x�N�g���̌����Ă�p�x�����߂�
float angle(const Vector2& v);
//�^�[�Q�b�g�����ւ̊p�x�����߂�
float angle(const Vector2& my, const Vector2& target);
//��̃x�N�g���̂Ȃ��p�x�����߂�
float innerAngle(const Vector2& a, const Vector2& b);
//�x�N�g���̐��`���
Vector2 lerp(const Vector2& start, const Vector2& end, float t);
//�^�[�Q�b�g�����ւ̊p�x�������߂�
float subtractAngle(const Vector2& my, float dir, const Vector2& target);
//��̓_�̒��_�����߂�
Vector2 middlePoint(Vector2 v1, Vector2 v2);

//�P�����Z�q�I�[�o�[���[�h
Vector2 operator+(const Vector2& v);
Vector2 operator-(const Vector2& v);

//������Z�q�I�[�o�[���[�h
Vector2& operator +=(Vector2& v1, const Vector2& v2);
Vector2& operator -=(Vector2& v1, const Vector2& v2);
Vector2& operator *=(Vector2& v, float s);
Vector2& operator /=(Vector2& v, float s);

//2�����Z�q�I�[�o�[���[�h
Vector2 operator +(const Vector2& v1, const Vector2& v2);
Vector2 operator -(const Vector2& v1, const Vector2& v2);
Vector2 operator*(const Vector2& v, float s);
Vector2 operator*(float s, const Vector2& v);
Vector2 operator/(const Vector2& v, float s);

#endif
