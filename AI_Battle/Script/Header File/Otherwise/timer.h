#ifndef TIMER_H_
#define TIMER_H_

class Timer
{
private:
	float timer;
	float endTime;

public:
	Timer();
	Timer(float time);
	void resetTimer();
	void update(float frameTime);
	bool isEnd();
	void changeEndTime(float endTime);
	float nowTime(){ return timer; }

};

#endif