#include"../../Header File/Otherwise/timer.h"

Timer::Timer()
{

}

Timer::Timer(float time)
{
	timer = 0;
	this->endTime = time;
}

/*タイマーのリセット*/
void Timer::resetTimer()
{
	timer = 0;
}

/*タイマーの更新*/
void Timer::update(float frameTimer)
{
	if (isEnd())return;
	timer += frameTimer;
}

/*タイマーが終了したかどうか*/
bool Timer::isEnd()
{
	return (timer >=endTime);
}

/*終了時間の変更*/
void Timer::changeEndTime(float endTime)
{
	this->endTime = endTime;
}