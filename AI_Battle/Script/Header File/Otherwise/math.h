#ifndef _MATH_UTILITY_H_
#define _MATH_UTILITY_H_

class Math
{
public:
	//�~����
	static const float PI;

	//�T�C��
	static float sin(float degree);
	//�R�T�C��
	static float cos(float degree);
	//�^���W�F���g
	static float tan(float degree);

	//�t�T�C��
	static float asin(float x);
	//�t�R�T�C��
	static float acos(float x);
	//�t�^���W�F���g
	static float atan(float y, float x);

	//�p�x�����W�A���ɕϊ�
	static float radian(float degree);
	//���W�A�����p�x�ɕϊ�
	static float degree(float radian);

	static float fmod(float x, float y);

	static float clamp(float x, float min, float max);

	static float abs(float num);

	static float Min(float num, float minNum);

	static float Max(float num,float maxNum);
};
#endif