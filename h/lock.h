#ifndef OS1_2018_LOCK_H_
#define OS1_2018_LOCK_H_

#define _lock asm pushf; asm cli;
#define _unlock asm popf;

class Lock{
private:

	Lock();

public:

	static unsigned char dispatchRequest; // explicit context switch 0-no 1-yes
	static unsigned char sysCallRoutine;
};

#endif
