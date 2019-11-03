#ifndef OS1_2018_IDLETHRD_H_
#define OS1_2018_IDLETHRD_H_

#include "Thread.h"

class IdleThread: public Thread{
public:

	IdleThread();

	~IdleThread(){}

	void run();

	ID id;
};

#endif
