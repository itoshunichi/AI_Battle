#ifndef LERPMOVE_H_
#define LERPMOVE_H_

#include"vector2.h"

class LerpMove
{
private:
	//�ړ������������W
	Vector2 position;
	//�ړ��J�n�ʒu
	Vector2 startPosition;
	//�ړ��I���ʒu
	Vector2 endPosition;
	//�ړ��ɂ����鎞��
	float time = 0;
	//�ړ��J�n����
	float startTime = 0;
	//�ړ��I������
	float elapsedTime = 0;
	//�I������
	bool isEnd = false;
	bool isMove = false;

public:
	LerpMove();
	void update(float frameTime);
	void startMove(Vector2 startPos, Vector2 endPos, float time);
	void movePosition(Vector2 *position);
	bool IsEnd(){ return isEnd; }

};
#endif