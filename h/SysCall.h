#ifndef _SYSCALL_H_
#define _SYSCALL_H_

#include "thread.h"
#include "Semaphor.h"
#include "event.h"

enum SysCall_ID {
	ThreadConstructor,
	ThreadDestructor,
	ThreadStart,
	ThreadWaitToComplete,
	ThreadSleep,
	Dispatch,
	SemaphoreConstructor,
	SemaphoreDestructor,
	SemaphoreWait,
	SemaphoreSignal,
	SemaphoreVal,
	EventConstructor,
	EventDestructor,
	EventWait,
	EventSignal
};

struct Arguments {
	SysCall_ID sysCallID;
	Thread* thread;
	Semaphore* sem;
	Event* event;
	PCB* pcb;
	Time timeToSleep;
	Time timeSlice;
	StackSize stackSize;
	int semInit;
	int semRet;
	int toBlock;
	IVTNo ivtNo;
	ID threadID;
	ID semID;
	ID evID;
};

class SysCall {
public:

	static void interrupt systemCall(...);

	static void interrupt systemCallReturn(...);

	static void initializeRoutine();

	static volatile PCB* runningKernelThread;

	static Arguments* arguments;
};

#endif
