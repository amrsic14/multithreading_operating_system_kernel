#ifndef OS1_2018_PCB_H_
#define OS1_2018_PCB_H_

#include "Queue.h"
#include "sleepQue.h"
#include "KrnlThrd.h"

typedef enum State {NEW, READY, RUNNING, BLOCKED, SLEEPING, FINISHED} State;
typedef unsigned int Time;
typedef unsigned long StackSize;
typedef int ID;

class Thread;
class Queue;
class sleepQueue;

class PCB{
public:

	unsigned* stack;
	unsigned bp,sp, ss;

	State state;

	StackSize stackSizeInBytes;
	Time timeSlice;

	Thread* myThread;
	KernelThread* myKernelThread;
	ID id;

	Queue blockedPCBs;


	static ID idGenerator;
	static Queue allPCBs; //Queue of all created PCBs
	static sleepQueue sleeping; //All sleeping threads

	static volatile PCB* runningPCB;
	static PCB* idlePCB;
	static PCB* kernelMainPCB;
	
	PCB(StackSize stackSize, Time timeSlice);
	PCB(StackSize stackSize, Time timeSlice, Thread* myThread);
	PCB(StackSize stackSize, Time timeSlice, KernelThread* myKernelThread);
	~PCB();

	void createStack();

	void createKernelStack();

	void start();

	void waitToComplete();

	static void sleep(Time timeToSleep);

};

#endif
