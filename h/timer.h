#ifndef OS1_2018_TIMER_H_
#define OS1_2018_TIMER_H_

class Timer{
private:

	Timer();

	static void interrupt (*oldRoutine)(...);

	static unsigned int tickCounter;

	friend class SysCall;

public:

	static void interrupt timer(...);

	static void initializeRoutine();

	static void restoreRoutine();
};

#endif
