#include"../../Header File/Otherwise/timer.h"

Timer::Timer()
{

}

Timer::Timer(float time)
{
	timer = 0;
	this->endTime = time;
}

/*�^�C�}�[�̃��Z�b�g*/
void Timer::resetTimer()
{
	timer = 0;
}

/*�^�C�}�[�̍X�V*/
void Timer::update(float frameTimer)
{
	if (isEnd())return;
	timer += frameTimer;
}

/*�^�C�}�[���I���������ǂ���*/
bool Timer::isEnd()
{
	return (timer >=endTime);
}

/*�I�����Ԃ̕ύX*/
void Timer::changeEndTime(float endTime)
{
	this->endTime = endTime;
}