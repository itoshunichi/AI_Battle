#ifndef LERPMOVE_H_
#define LERPMOVE_H_

#include"vector2.h"

class LerpMove
{
private:
	//移動させたい座標
	Vector2 position;
	//移動開始位置
	Vector2 startPosition;
	//移動終了位置
	Vector2 endPosition;
	//移動にかかる時間
	float time = 0;
	//移動開始時間
	float startTime = 0;
	//移動終了時間
	float elapsedTime = 0;
	//終了判定
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