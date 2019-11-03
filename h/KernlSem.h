#ifndef OS1_2018_KERNLSEM_H_
#define OS1_2018_KERNLSEM_H_

#include "Queue.h"
#include "SemQue.h"

class PCB;
class Semaphore;

class KernelSem{
public:

	KernelSem(int init, Semaphore* mySem);

	~KernelSem();

	void block();

	void unblock();

	int wait(int toBlock);

	void signal();

	static SemQueue allSemaphores;
	static ID semIdGenerator;

	ID id;
	Semaphore* mySem;
	Queue waitList;
	int value;
};

#endif
