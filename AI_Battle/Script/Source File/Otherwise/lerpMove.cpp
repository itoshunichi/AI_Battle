#include"../../Header File/Otherwise/lerpMove.h"

LerpMove::LerpMove()
{

}

//更新
void LerpMove::update(float frameTime)
{
	elapsedTime += frameTime;
}

//移動開始
void LerpMove::startMove(Vector2 startPos, Vector2 endPos, float time)
{
	startTime = elapsedTime;
	startPosition = startPos;
	endPosition = endPos;
	this->time = time;
	isMove = true;
	isEnd = false;
}

//移動処理
void LerpMove::movePosition(Vector2 *position)
{
	if (isMove)
	{
		float dift = elapsedTime - startTime;
		float rate = dift / time;
		*position = lerp(startPosition, endPosition, rate);
		if (dift > time)
		{
			isEnd = true;
			isMove = false;
		}
	}

}